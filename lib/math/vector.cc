/* vim: set ts=4 sw=4 tw=79 et :*/
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "vector.h"
#include <math.h>

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
    z /= aValue,
}

void Vector3::operator-=(const Vector3& aVector) {
    x -= aVector.x;
    y -= aVector.y;
    z -= aVector.z;
}

void Vector3::normalize() {
    real length = magnitude();

    if (length != 0) {
        (*this) *= 1.0f / length;
    }
}

void Vector3::addScaledVector(const Vector3& aVector, real aScale) {
    x += aVector.x * aScale;
    y += aVector.y * aScale;
    z += aVector.z * aScale;
}

Vector3 Vector3::componentProduct(const Vector3& aVector) const {
    return Vector3(
            x * aVector.x,
            y * aVector.y,
            z * aVector.z);
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
    *this = vectorProduct(aVector);
}

}}
