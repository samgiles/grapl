/* vim: set ts=4 sw=4 tw=79 et :*/
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "vector.h"
#include <math.h>

#ifdef _USE_SIMD
#include "emmintrin.h"
#endif

namespace grapl { namespace math {

void Vector3::invert() {
    x = -x;
    y = -y;
    z = -z;
}

real Vector3::squareMagnitude() const {
    return x * x + y * y + z * z;
}

real Vector3::magnitude() const {
    return sqrt(squareMagnitude());
}

void Vector3::operator+=(const real aValue) {
    x += aValue;
    y += aValue;
    z += aValue;
}

void Vector3::operator+=(const Vector3& aVector) {
    x += aVector.x;
    y += aVector.y;
    z += aVector.z;
}

void Vector3::operator*=(const real aValue) {
    x *= aValue;
    y *= aValue;
    z *= aValue;
}

Vector3 Vector3::operator*(const real aValue) {
    return Vector3(
            x * aValue,
            y * aValue,
            z * aValue);
}

void Vector3::operator/=(const real aValue) {
    x /= aValue;
    y /= aValue;
    z /= aValue;
}

void Vector3::operator-=(const Vector3& aVector) {
    x -= aVector.x;
    y -= aVector.y;
    z -= aVector.z;
}

void Vector3::normalize() {
    real length = magnitude();

    if (length != 0) {
        // XXX: Wonder if ((*this) *= 1.0f/length; is faster (less divs)
        (*this) /= length;
    }
}

void Vector3::addScaledVector(const Vector3& aVector, real aScale) {
#ifdef _USE_SIMD
    const __m128 thisVec      = _mm_load_ps((real*)this);
    const __m128 vec          = _mm_load_ps((real*)&aVector);
    const __m128 scalar       = _mm_set1_ps(aScale);
    const __m128 scaledResult = _mm_mul_ps(vec, scalar);
    const __m128 addedResult  = _mm_add_ps(thisVec, scaledResult);
    _mm_store_ps((float*)this, addedResult);
#else
    x += aVector.x * aScale;
    y += aVector.y * aScale;
    z += aVector.z * aScale;
#endif
}

Vector3 Vector3::componentProduct(const Vector3& aVector) const {
#ifdef _USE_SIMD
    Vector3 resultVector;

    const __m128 thisVec = _mm_load_ps((real*)this);
    const __m128 vec     = _mm_load_ps((real*)&aVector);
    const __m128 result  = _mm_mul_ps(thisVec, vec);
    _mm_store_ps((float*)&resultVector, result);
    return resultVector;
#else
    return Vector3(
            x * aVector.x,
            y * aVector.y,
            z * aVector.z);
#endif
}

void Vector3::componentProductUpdate(const Vector3& aVector) {
    x *= aVector.x;
    y *= aVector.y;
    z *= aVector.z;
}

real Vector3::scalarProduct(const Vector3& aVector) const {
    return
        x * aVector.x +
        y * aVector.y +
        z * aVector.z;
}

real Vector3::operator*(const Vector3& aVector) const {
    return scalarProduct(aVector);
}

Vector3 Vector3::vectorProduct(const Vector3& aVector) const {
    return Vector3(
            y * aVector.z - z * aVector.y,
            z * aVector.x - x * aVector.z,
            x * aVector.y - y * aVector.x);
}

void Vector3::vectorProductUpdate(const Vector3& aVector) {
    (*this) = vectorProduct(aVector);
}

}}
