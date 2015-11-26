/* vim: set ts=4 sw=4 tw=79 et :*/
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

// Core
#define MODULE 1
ERROR(GR_OK,                  SUCCESS(0)),

ERROR(GR_ERROR_BASE,          FAILURE(0)),
ERROR(GR_ERROR_FAILURE,       FAILURE(1)),
ERROR(GR_ERROR_INVALID_ARGS,  FAILURE(2)),
ERROR(GR_ERROR_OUT_OF_MEMORY, FAILURE(3))
#undef MODULE
