#include "window.h"
#include <algorithm>
#include <atomic>
#include <mutex>
#include <memory>
#include <execution>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cstring>

extern "C" {
#include <spvm/context.h>
#include <spvm/state.h>
#include <spvm/ext/GLSL450.h>
}

using spv_source = std::vector<spvm_word>;
constexpr int N_THREADS = 8;
constexpr int N_FRAGMENT_PER_GROUP = 64;

struct spv_thread {
	std::unique_ptr<std::mutex> mutex;

	spvm_state_t state;

	spvm_result_t uBlock;
	spvm_member_t uBlock_time;
	spvm_member_t uBlock_info;
	spvm_word fnMain;
	spvm_result_t outColor;

	spv_thread(spvm_state_t state, spvm_ext_opcode_func* glsl_ext_data) : state(state), mutex(new std::mutex) {
		spvm_result_t glsl_std_450 = spvm_state_get_result(state, "GLSL.std.450");
		if (glsl_std_450)
			glsl_std_450->extension = glsl_ext_data;

		// get uBlock
		uBlock = spvm_state_get_result(state, "uBlock");
		uBlock_time = spvm_state_get_object_member(state, uBlock, "time");
		uBlock_info = spvm_state_get_object_member(state, uBlock, "info");
		fnMain = spvm_state_get_result_location(state, "main");

		// get outColor
		outColor = spvm_state_get_result(state, "outColor");
		if (outColor->type != spvm_result_type_variable || outColor->member_count != 4) {
			std::cerr << "outColor must be a vec4 variable" << std::endl;
			std::exit(EXIT_FAILURE);
		}
	}
};

struct fragment {
	int x, y;
};
using fragment_group = std::vector<fragment>;

spv_source load_source(const char* fname) {
	std::ifstream file(fname, std::ios::binary | std::ios::ate);
	if (!file.is_open()) {
		std::cerr << "can not open source file: " << fname << std::endl;
		std::exit(EXIT_FAILURE);
	}

	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);

	size_t source_size = size / sizeof(spvm_word);
	if (source_size * sizeof(spvm_word) != size) {
		std::cerr << "incorrect source size: " << size << std::endl;
		std::exit(EXIT_FAILURE);
	}

	spv_source source(source_size);
	if (file.read(reinterpret_cast<char*>(source.data()), size))
	{
		return source;
	}
	else {
		std::cerr << "source file read failed!" << std::endl;
		std::exit(EXIT_FAILURE);
	}
}

int main(int argv, char** argc) {
	if (argv < 2) {
		std::cout << "Usage: SPIRVVM-simulator <source file>" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	Window window(640, 360, "SPIRV-Simulator");

	// context holds all opcode functions
	spvm_context_t ctx = spvm_context_initialize();

	// load source code
	spv_source spv = load_source(argc[1]);

	// create a program
	spvm_program_t prog = spvm_program_create(ctx, spv.data(), spv.size());

	// load extension
	spvm_ext_opcode_func* glsl_ext_data = spvm_build_glsl450_ext();

	// create states for all threads
	std::vector<spv_thread> threads;
	for (int i = 0; i < N_THREADS; i++) {
		threads.emplace_back(spvm_state_create(prog), glsl_ext_data);
	}

	// create fragment groups
	std::vector<fragment_group> fragment_groups;
	fragment_group fragments;
	for (int y = 0; y < window.height(); y++) {
		for (int x = 0; x < window.width(); x++) {
			fragments.push_back({ x, y });

			if (fragments.size() >= N_FRAGMENT_PER_GROUP)
				fragment_groups.push_back(std::move(fragments));
		}
	}
	if (fragments.size()) {
		fragment_groups.push_back(std::move(fragments));
	}

	clock_t start_time = clock();
	while (window.is_run()) {
		// set uBlock.time
		float elapsed_time = float(clock() - start_time) * (1.0f / CLOCKS_PER_SEC);

		std::atomic<size_t> total_discarded = 0;
		std::atomic<size_t> thread_index = 0;

		std::for_each(
			std::execution::par_unseq,
			fragment_groups.begin(),
			fragment_groups.end(),
			[&](const fragment_group& frag_group)
			{
				size_t idx = thread_index.fetch_add(1);
				spv_thread& t = threads[idx % N_THREADS];
				std::lock_guard<std::mutex> lock(*t.mutex);

				for (fragment f : frag_group) {
					t.uBlock_time->value.f = elapsed_time;

					// set uBlock.info
					float fragCoord[2] = { (float)f.x / window.width(), (float)f.y / window.height() };
					spvm_member_set_value_f(t.uBlock_info->members, t.uBlock_info->member_count, fragCoord);

					// call main
					spvm_state_prepare(t.state, t.fnMain);
					spvm_state_call_function(t.state);

					// set outcolor to frame buffer
					float r = t.outColor->members[0].value.f;
					float g = t.outColor->members[1].value.f;
					float b = t.outColor->members[2].value.f;
					float a = t.outColor->members[3].value.f;

					int ir = std::clamp(int(r * 255), 0, 255);
					int ig = std::clamp(int(g * 255), 0, 255);
					int ib = std::clamp(int(b * 255), 0, 255);
					int ia = std::clamp(int(a * 255), 0, 255);

					int color = (ir << 16) | (ig << 8) | ib;
					*window(f.x, f.y) = color;

					// accumulate pixel count that discarded
					total_discarded.fetch_add(t.state->discarded);
				}
			});

		std::cout << "total discarded: " << total_discarded << "\n";
		window.update();
		window.set_title(("SPIRV-Simulator (fps: " + std::to_string(window.get_fps()) + ")").c_str());
	}

	// free memory
	for (spv_thread& th : threads) {
		spvm_state_delete(th.state);
	}
	spvm_program_delete(prog);
	free(glsl_ext_data);

	spvm_context_deinitialize(ctx);
}