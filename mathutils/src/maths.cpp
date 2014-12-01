/*
 * maths.cpp
 *
 *  Created on: Nov 9, 2014
 *      Author: mrgame64
 */

#include "mathutils.hpp"

using namespace math;

#ifndef PRECISE
#ifndef SIN_BITS
#define SIN_BITS 16
#endif
#define SIN_MASK (~(-1 << SIN_BITS))
#define SIN_COUNT (SIN_MASK + 1)
const fp radToIndex = SIN_COUNT / radFull;
const fp degToIndex = SIN_COUNT / degFull;

fp sin_table[SIN_COUNT];
bool sin_gen;


void gen_sin_table() {
	for (int i = 0; i < SIN_COUNT; i++)
		sin_table[i] = std::sin((i + 0.5f) / SIN_COUNT * radFull);
	for (int i = 0; i < 360; i += 90)
		sin_table[(int)(i * degToIndex) & SIN_MASK] = std::sin(i * degRad);
	sin_gen = true;
};
#endif

fp sin(fp rad) {
#ifndef PRECISE
	if(!sin_gen)
		gen_sin_table();
	return sin_table[(int)(rad * radToIndex) & SIN_MASK];
#else
	return std::sin(rad);
#endif
};

fp cos(fp rad) {
#ifndef PRECISE
	if(!sin_gen)
		gen_sin_table();
	return sin_table[(int)((rad + PI / 2) * radToIndex) & SIN_MASK];
#else
	return std::cos(rad);
#endif
};

fp sin_deg(fp deg) {
#ifndef PRECISE
	if(!sin_gen)
		gen_sin_table();
	return sin_table[(int)(deg * degToIndex) & SIN_MASK];
#else
	return std::sin(deg * degRad);
#endif
};

fp cos_deg(fp deg) {
#ifndef PRECISE
	if(!sin_gen)
		gen_sin_table();
	return sin_table[(int)((deg + 90) * degToIndex) & SIN_MASK];
#else
	return std::cos(deg * degRad);
#endif
};

#ifndef PRECISE
#ifndef ATAN2_BITS
#define ATAN2_BITS 8 // Adjust for accuracy.
#endif
#define ATAN2_BITS2 ATAN2_BITS << 1
#define ATAN2_MASK ~(-1 << ATAN2_BITS2)
#define ATAN2_COUNT ATAN2_MASK + 1
#define ATAN2_DIM (int)sqrt(ATAN2_COUNT)
#define INV_ATAN2_DIM_MINUS_1 1.0f / (ATAN2_DIM - 1)

fp atan2_table[ATAN2_COUNT];
bool atan2_gen;
#endif

fp atan2(fp y, fp x) {
#ifndef PRECISE

#else
	return std::atan2(y, x);
#endif
}
