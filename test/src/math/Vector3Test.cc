/* vim: set ts=4 sw=4 tw=79 et :*/
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "TestHarness.h"

#include "math/vector.h"

int main(int argc, char* argv[]) {
    int rv = 0;

    rv +=
    runTest("Vector3 invert", []() {
        grapl::math::Vector3* vec = new grapl::math::Vector3(10.0f, 11.0f, 12.0f);

        vec->invert();

        return
            vec->x == -10.0f &&
            vec->y == -11.0f &&
            vec->z == -12.0f;
    });

    return rv;
}
