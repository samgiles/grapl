#ifndef TestHarness_h__
#define TestHarness_h__

#include "base/Error.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

static uint32_t gFailCount = 0;

void _testStatusMessage(const char* status, const char* message, va_list args) {
    printf("%s | ", status);

    vprintf(message, args);

    putchar('\n');
}

void fail(const char* message, ...) {
    va_list args;
    va_start(args, message);
    _testStatusMessage("TEST-UNEXPECTED-FAIL", message, args);
    va_end(args);
    ++gFailCount;
}

void pass(const char* message, ...) {
    va_list args;
    va_start(args, message);
    _testStatusMessage("TEST-PASS", message, args);
    va_end(args);
}


#endif // TestHarness_h__
