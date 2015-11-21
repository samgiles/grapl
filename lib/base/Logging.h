/* vim: set ts=4 sw=4 tw=79 et :*/
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef Logging_h__
#define Logging_h__

#include <stdio.h>
#include <stdarg.h>

void _grapl_print_log(const char* priority, const char* message, ...) {
    va_list args;
    printf("%s | ", priority);
    va_start(args, message);
    vprintf(message, args);
    va_end(args);
    putchar('\n');
}

#ifdef DEBUG

#define LOG(priority, tag, ...) _grapl_print_log(priority, tag, ##__VA_ARGS__)

#else

#define LOG(priority, tag, ...) do { } while(0)

#endif //DEBUG


#define LOG_VERBOSE "VERBOSE"
#define LOG_DEBUG   "DEBUG"
#define LOG_INFO    "INFO"
#define LOG_WARN    "WARN"
#define LOG_ERROR   "ERROR"

#define ERR(tag, ...) _grapl_print_log("ERROR", tag, ##__VA_ARGS__)

#endif // Logging_h__
