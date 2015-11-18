/* vim: set ts=4 sw=4 tw=79 et :*/
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef Error_h__
#define Error_h__

#include <stdint.h>
#include "Likely.h"

#define ERROR_SEVERITY_SUCCESS 0x0
#define ERROR_SEVERITY_FAILURE 0x1

/* Module List */

#define ERROR_MODULE_BASE   1

#define ERROR_MODULE_BASE_OFFSET 0x45

#define SUCCESS_OR_FAILURE(sev, module, code) \
    ((uint32_t)(sev) << 31) | \
    ((uint32_t)(module + ERROR_MODULE_BASE_OFFSET) << 16) | \
    (uint32_t)(code)

#define FAILURE(code) \
    SUCCESS_OR_FAILURE(ERROR_SEVERITY_FAILURE, MODULE, code)

#define SUCCESS(code) \
    SUCCESS_OR_FAILURE(ERROR_SEVERITY_SUCCESS, MODULE, code)

enum class resultv : uint32_t {
    #undef ERROR
    #define ERROR(key, val) key = val
    #include "ErrorList.h"
    #undef ERROR
};

/*
 * enum classes don't place their initializers in the global scope, so we need
 * constants for compatibility with old code.
 */
const resultv
  #define ERROR(key, val) key = resultv::key
  #include "ErrorList.h"
  #undef ERROR
;

#undef SUCCESS_OR_FAILURE
#undef SUCCESS
#undef FAILURE

inline uint32_t R_FAILED_impl(resultv aCode) {

    return static_cast<uint32_t>(aCode) & 0x80000000;
}

#define R_FAILED(_resultv)      ((bool)HINT_BP_UNLIKELY(R_FAILED_impl(_resultv)))
#define R_SUCCEEDED(_resultv)   ((bool)HINT_BP_LIKELY(!R_FAILED_impl(_resultv)))

/* Check that our enum type is actually uint32_t as expected */
static_assert(((resultv)0) < ((resultv)-1), "resultv must be an unsigned type");
static_assert(sizeof(resultv) == sizeof(uint32_t), "resultv must be 32 bits");

#endif // Error_h__
