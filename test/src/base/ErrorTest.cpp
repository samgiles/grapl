/* vim: set ts=4 sw=4 tw=79 et :*/
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "TestHarness.h"

int main(int argc, char* argv[]) {
    int rv = 0;

    rv+=
    runTest("Test R_FAILED", []() {
        return static_cast<bool>(GR_FAILED(GR_ERROR_FAILURE));
    });

    rv+=
    runTest("Test R_SUCCEEDED", []() {
        return static_cast<bool>(GR_SUCCEEDED(GR_OK));
    });

    return rv;
}

