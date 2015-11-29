/* vim: set ts=4 sw=4 tw=79 et :*/
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#pragma once

#include "emmintrin.h"

namespace grapl { namespace math { namespace simd {

typedef void (*SimdCommand) (__m128*, __m128&);

inline __m128 createScalar(float aValue) {
    return _mm_set1_ps(aValue);
}

inline __m128 loadAligned(float* aValue) {
    return _mm_load_ps(aValue);
}

inline void storeAligned(float* aDestination, __m128 aSource) {
    _mm_store_ps(aDestination, aSource);
}

inline void simdMultiply(__m128* dest, __m128& source) {
    *dest = _mm_mul_ps(*dest, source);
}

inline void simdAdd(__m128* dest, __m128& source) {
    *dest = _mm_add_ps(*dest, source);
}

inline void simdDiv(__m128* dest, __m128& source) {
    *dest = _mm_div_ps(*dest, source);
}

inline void simdSqrt(__m128* dest, __m128& source) {
    *dest = _mm_sqrt_ps(source);
}

}}}
