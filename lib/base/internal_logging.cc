/* vim: set ts=4 sw=4 tw=79 et :*/
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <stdio.h>
#include <stdarg.h>
#include "internal_logging.h"

void _grapl_print_log(const char* priority, const char* message, ...) {
    va_list args;
    printf("%s | ", priority);
    va_start(args, message);
    vprintf(message, args);
    va_end(args);
    putchar('\n');
}

