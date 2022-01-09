/*
** Copyright (c) 2015-2017 The Khronos Group Inc.
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and/or associated documentation files (the "Materials"),
** to deal in the Materials without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense,
** and/or sell copies of the Materials, and to permit persons to whom the
** Materials are furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in
** all copies or substantial portions of the Materials.
**
** MODIFICATIONS TO THIS FILE MAY MEAN IT NO LONGER ACCURATELY REFLECTS KHRONOS
** STANDARDS. THE UNMODIFIED, NORMATIVE VERSIONS OF KHRONOS SPECIFICATIONS AND
** HEADER INFORMATION ARE LOCATED AT https://www.khronos.org/registry/
**
** THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
** OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
** FROM,OUT OF OR IN CONNECTION WITH THE MATERIALS OR THE USE OR OTHER DEALINGS
** IN THE MATERIALS.
*/

#pragma once

enum Entrypoints {

	// Section 2.1: Math extended instructions
	CL_Acos = 0,
	CL_Acosh = 1,
	CL_Acospi = 2,
	CL_Asin = 3,
	CL_Asinh = 4,
	CL_Asinpi = 5,
	CL_Atan = 6,
	CL_Atan2 = 7,
	CL_Atanh = 8,
	CL_Atanpi = 9,
	CL_Atan2pi = 10,
	CL_Cbrt = 11,
	CL_Ceil = 12,
	CL_Copysign = 13,
	CL_Cos = 14,
	CL_Cosh = 15,
	CL_Cospi = 16,
	CL_Erfc = 17,
	CL_Erf = 18,
	CL_Exp = 19,
	CL_Exp2 = 20,
	CL_Exp10 = 21,
	CL_Expm1 = 22,
	CL_Fabs = 23,
	CL_Fdim = 24,
	CL_Floor = 25,
	CL_Fma = 26,
	CL_Fmax = 27,
	CL_Fmin = 28,
	CL_Fmod = 29,
	CL_Fract = 30,
	CL_Frexp = 31,
	CL_Hypot = 32,
	CL_Ilogb = 33,
	CL_Ldexp = 34,
	CL_Lgamma = 35,
	CL_Lgamma_r = 36,
	CL_Log = 37,
	CL_Log2 = 38,
	CL_Log10 = 39,
	CL_Log1p = 40,
	CL_Logb = 41,
	CL_Mad = 42,
	CL_Maxmag = 43,
	CL_Minmag = 44,
	CL_Modf = 45,
	CL_Nan = 46,
	CL_Nextafter = 47,
	CL_Pow = 48,
	CL_Pown = 49,
	CL_Powr = 50,
	CL_Remainder = 51,
	CL_Remquo = 52,
	CL_Rint = 53,
	CL_Rootn = 54,
	CL_Round = 55,
	CL_Rsqrt = 56,
	CL_Sin = 57,
	CL_Sincos = 58,
	CL_Sinh = 59,
	CL_Sinpi = 60,
	CL_Sqrt = 61,
	CL_Tan = 62,
	CL_Tanh = 63,
	CL_Tanpi = 64,
	CL_Tgamma = 65,
	CL_Trunc = 66,
	CL_Half_cos = 67,
	CL_Half_divide = 68,
	CL_Half_exp = 69,
	CL_Half_exp2 = 70,
	CL_Half_exp10 = 71,
	CL_Half_log = 72,
	CL_Half_log2 = 73,
	CL_Half_log10 = 74,
	CL_Half_powr = 75,
	CL_Half_recip = 76,
	CL_Half_rsqrt = 77,
	CL_Half_sin = 78,
	CL_Half_sqrt = 79,
	CL_Half_tan = 80,
	CL_Native_cos = 81,
	CL_Native_divide = 82,
	CL_Native_exp = 83,
	CL_Native_exp2 = 84,
	CL_Native_exp10 = 85,
	CL_Native_log = 86,
	CL_Native_log2 = 87,
	CL_Native_log10 = 88,
	CL_Native_powr = 89,
	CL_Native_recip = 90,
	CL_Native_rsqrt = 91,
	CL_Native_sin = 92,
	CL_Native_sqrt = 93,
	CL_Native_tan = 94,

	// Section 2.2: Integer instructions
	CL_SAbs = 141,
	CL_SAbs_diff = 142,
	CL_SAdd_sat = 143,
	CL_UAdd_sat = 144,
	CL_SHadd = 145,
	CL_UHadd = 146,
	CL_SRhadd = 147,
	CL_URhadd = 148,
	CL_SClamp = 149,
	CL_UClamp = 150,
	CL_Clz = 151,
	CL_Ctz = 152,
	CL_SMad_hi = 153,
	CL_UMad_sat = 154,
	CL_SMad_sat = 155,
	CL_SMax = 156,
	CL_UMax = 157,
	CL_SMin = 158,
	CL_UMin = 159,
	CL_SMul_hi = 160,
	CL_Rotate = 161,
	CL_SSub_sat = 162,
	CL_USub_sat = 163,
	CL_U_Upsample = 164,
	CL_S_Upsample = 165,
	CL_Popcount = 166,
	CL_SMad24 = 167,
	CL_UMad24 = 168,
	CL_SMul24 = 169,
	CL_UMul24 = 170,
	CL_UAbs = 201,
	CL_UAbs_diff = 202,
	CL_UMul_hi = 203,
	CL_UMad_hi = 204,

	// Section 2.3: Common instructions
	CL_FClamp = 95,
	CL_Degrees = 96,
	CL_FMax_common = 97,
	CL_FMin_common = 98,
	CL_Mix = 99,
	CL_Radians = 100,
	CL_Step = 101,
	CL_Smoothstep = 102,
	CL_Sign = 103,

	// Section 2.4: Geometric instructions
	CL_ross = 104,
	CL_istance = 105,
	CL_ength = 106,
	CL_ormalize = 107,
	CL_ast_distance = 108,
	CL_ast_length = 109,
	CL_ast_normalize = 110,

	// Section 2.5: Relational instructions
	CL_Bitselect = 186,
	CL_Select = 187,

	// Section 2.6: Vector Data Load and Store instructions
	CL_Vloadn = 171,
	CL_Vstoren = 172,
	CL_Vload_half = 173,
	CL_Vload_halfn = 174,
	CL_Vstore_half = 175,
	CL_Vstore_half_r = 176,
	CL_Vstore_halfn = 177,
	CL_Vstore_halfn_r = 178,
	CL_Vloada_halfn = 179,
	CL_Vstorea_halfn = 180,
	CL_Vstorea_halfn_r = 181,

	// Section 2.7: Miscellaneous Vector instructions
	CL_Shuffle = 182,
	CL_Shuffle2 = 183,

	// Section 2.8: Misc instructions 
	CL_Printf = 184,
	CL_Prefetch = 185,
};
