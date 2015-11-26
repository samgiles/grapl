/* vim: set ts=4 sw=4 tw=79 et :*/
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#pragma once

#include <stddef.h>
#include "base/Error.h"

namespace grapl {

class IMalloc {
    public:
        virtual resultv malloc(size_t aSize, uint32_t aAlignment, void** aOut) = 0;
        virtual resultv realloc(void** aPtr, size_t aNewSize, uint32_t aAlignment) = 0;
        virtual void free(void* aPtr) = 0;
        virtual size_t allocSize(void* aPtr) = 0;
};

}

#include "base/memory/system_malloc.h"

