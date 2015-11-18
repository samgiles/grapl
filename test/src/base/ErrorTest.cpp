/* vim: set ts=4 sw=4 tw=79 et :*/

#include "TestHarness.h"

/**
 * This test simply tests the test harness..
 * Well, we want to make sure it works right?
 */

resultv Test_R_FAILED() {
    if (!R_FAILED(R_ERROR_FAILURE)) {
        fail("R_FAILED");
        return R_ERROR_FAILURE;
    }

    pass("R_FAILED");
    return R_OK;
}

resultv Test_R_SUCCEEDED() {
    if (!R_SUCCEEDED(R_OK)) {
        fail("R_SUCCEEDED");
        return R_ERROR_FAILURE;
    }

    pass("R_SUCCEEDED");
    return R_OK;
}

int main(int argc, char* argv[]) {
    int rv = 0;

    if (Test_R_FAILED() != R_OK) {
        rv = 1;
    }

    if (Test_R_SUCCEEDED() != R_OK) {
        rv = 1;
    }

    return rv;
}

