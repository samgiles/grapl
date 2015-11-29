/* vim: set ts=4 sw=4 tw=79 et :*/
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef math_vector_h__
#define math_vector_h__

#include "precision.h"
#include "base/memory.h"

namespace grapl {
namespace math {

class ALIGN(16) Vector3 final {
    public:
        float x;
        float y;
        float z;
        float w;

    public:
        Vector3() : x(0), y(0), z(0) {}
        Vector3(const float aX, const float aY, const float aZ) :
            x(aX), y(aY), z(aZ) {
        }

        /* Invert the components of the vector */
        void invert();

        float magnitude() const;
        float squareMagnitude() const;

        void normalize();

        void addScaledVector(const Vector3& aVector, float aScale);

        Vector3 componentProduct(const Vector3& aVector) const;
        void componentProductUpdate(const Vector3& aVector);

        float scalarProduct(const Vector3& aVector) const;
        float operator*(const Vector3& aVector) const;

        Vector3 vectorProduct(const Vector3& aVector) const;
        void vectorProductUpdate(const Vector3& aVector);

        void operator/=(const float aValue);

        void operator*=(const float aValue);
        Vector3 operator*(const float aValue);

        void operator+=(const float aValue);
        void operator+=(const Vector3& aVector);

        void operator-=(const Vector3& aVector);
};

}
}
#endif // math_vector_h__
