/* vim: set ts=4 sw=4 tw=79 et :*/
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef math_vector_h__
#define math_vector_h__

#include "precision.h"

namespace grapl {
namespace math {

class Vector3 {
    public:
        real x;
        real y;
        real z;
    private:
        /* Four word alignment */
        real _pad;

    public:
        Vector3() : x(0), y(0), z(0) {}
        Vector3(const real aX, const real aY, const real aZ) :
            x(aX), y(aY), z(aZ) {
        }

        /* Invert the components of the vector */
        void invert();

        real magnitude() const;
        real squareMagnitude() const;

        void normalize();

        void operator/=(const real aValue);

        void operator*=(const real aValue);
        Vector3 operator*(const real aValue);

        void operator+=(const real aValue);
        void operator+=(const Vector3& aVector);
};
}
}
#endif // math_vector_h__
