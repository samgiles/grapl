/* vim: set ts=4 sw=4 tw=79 et :*/
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/* BP_LIKELY and BP_UNLIKELY give branch prediction hints to the compiler */

#pragma once

#if defined(__clang__) || defined(__GNUC__)
#  define HINT_BP_LIKELY(x)   (__builtin_expect(!!(x), 1))
#  define HINT_BP_UNLIKELY(x) (__builtin_expect(!!(x), 0))
#else
#  define HINT_BP_LIKELY(x)   (!!(x))
#  define HINT_BP_UNLIKELY(x) (!!(x))
#endif

