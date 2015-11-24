/* vim: set ts=4 sw=4 tw=79 et :*/
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "TestHarness.h"

#include "math/vector.h"

using namespace grapl::math;

bool assertApprox(grapl::real aIn, grapl::real aExpected, grapl::real aError) {
    if (aIn > (aExpected + aError)) {
        return false;
    } else if (aIn < (aExpected - aError)) {
        return false;
    }

    return true;
}

int main(int argc, char* argv[]) {
    int rv = 0;

    rv +=
    runTest("Vector3 invert", []() {
        Vector3 vec = Vector3(10.0f, 11.0f, 12.0f);

        vec.invert();

        return
            vec.x == -10.0f &&
            vec.y == -11.0f &&
            vec.z == -12.0f;
    });

    rv +=
    runTest("Vector3 squaredMagnitude", []() {
        Vector3 vec = Vector3(16.0f, 8.0f, 4.0f);
        grapl::real result = vec.squareMagnitude();

        return result == 336.0f;
    });

    rv +=
    runTest("Vector3 magnitude", []() {
        Vector3 vec = Vector3(16.0f, 8.0f, 4.0f);
        grapl::real result = vec.magnitude();
        return assertApprox(result, 18.33030278f, 0.000001f);
    });

    rv +=
    runTest("Vector3 operator *=", []() {
        Vector3 vec = Vector3(2.0f, 2.0f, 2.0f);
        vec *= 2.0f;

        return
            vec.x == 4.0f  &&
            vec.y == 4.0f  &&
            vec.z == 4.0f;
    });

    rv +=
    runTest("Vector3 operation *", []() {
        Vector3 vec = Vector3(2.0f, 2.0f, 2.0f);
        Vector3 result = vec * 2.0f;

        return
            result.x == 4.0f  &&
            result.y == 4.0f  &&
            result.z == 4.0f;
    });

    rv +=
    runTest("Vector3 normalize", []() {
        Vector3 vec = Vector3(2.0f, 2.0f, 2.0f);
        vec.normalize();

        return
            assertApprox(vec.x, 0.5773502692f, 0.000001f) &&
            assertApprox(vec.y, 0.5773502692f, 0.000001f) &&
            assertApprox(vec.z, 0.5773502692f, 0.000001f);
    });

    rv +=
    runTest("Vector3 += scalar", []() {
        Vector3 vec = Vector3(2.0f, 2.0f, 2.0f);
        vec += 2.0f;
        return
            vec.x == 4.0f  &&
            vec.y == 4.0f  &&
            vec.z == 4.0f;
    });

    rv +=
    runTest("Vector3 += vec", []() {
        Vector3 vec = Vector3(2.0f, 2.0f, 2.0f);
        Vector3 other = Vector3(3.0f, 4.0f, 5.0f);

        vec += other;

        return
            vec.x == 5.0f &&
            vec.y == 6.0f &&
            vec.z == 7.0f;
    });

    rv +=
    runTest("Vector3 -= vec", []() {
        Vector3 vec = Vector3(3.0f, 3.0f, 2.0f);
        Vector3 other = Vector3(1.0f, 1.0f, 1.0f);

        vec -= other;

        return
            vec.x == 2.0f &&
            vec.y == 2.0f &&
            vec.z == 1.0f;
    });

    rv +=
    runTest("Vector3 addScaledVector", []() {
        Vector3 vec = Vector3(1.0f, 2.0f, 3.0f);
        Vector3 other = Vector3(2.0f, 2.0f, 2.0f);

        vec.addScaledVector(other, 2.0f);

        return
            vec.x == 5.0f &&
            vec.y == 6.0f &&
            vec.z == 7.0f;
    });

    rv +=
    runTest("Vector3 addScaledVector should be equivalent of scale then add", []() {
        Vector3 vecA = Vector3(1.0f, 2.0f, 3.0f);
        Vector3 vecB = Vector3(1.0f, 2.0f, 3.0f);
        Vector3 other = Vector3(2.0f, 2.0f, 2.0f);

        vecA.addScaledVector(other, 2.0f);

        Vector3 scaled = other * 2.0f;
        vecB += scaled;

        return
            vecA.x == vecB.x &&
            vecA.y == vecB.y &&
            vecA.z == vecB.z;
    });

    rv +=
    runTest("Vector3 componentProduct", []() {
        Vector3 vecA = Vector3(2.0f, 2.0f, 2.0f);
        Vector3 vecB = Vector3(3.0f, 4.0f, 5.0f);

        Vector3 result = vecA.componentProduct(vecB);

        return
            result.x == 6.0f &&
            result.y == 8.0f &&
            result.z == 10.0f;
    });

    rv +=
    runTest("Vector3 componentProductUpdate", []() {
        Vector3 vecA = Vector3(2.0f, 2.0f, 2.0f);
        Vector3 vecB = Vector3(3.0f, 4.0f, 5.0f);

        vecA.componentProductUpdate(vecB);

        return
            vecA.x == 6.0f &&
            vecA.y == 8.0f &&
            vecA.z == 10.0f;
    });

    return rv;
}
