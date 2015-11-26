/* vim: set ts=4 sw=4 tw=79 et :*/
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "system_malloc.h"
#include "base/Likely.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * How does __aligned_malloc work?
 *
 *  Firstly, it's important to note, that Apple's malloc implementation will
 *  return a 16 byte aligned address, but, for the purposes of generality,
 *  cross platform, and academia as a base for aligning memory from a custom,
 *  userland, allocator, we implement this algorithm.
 *
 *  The general idea is to allocate enough memory to store a reference to the
 *  original allocated memory, the size and enough to pad to the requested
 *  alignment.
 *
 *  In this example, imagine this was called as such:
 *      __aligned_malloc((size_t)24, (uint32_t)16);
 *
 *  Inside this method, malloc would be called as such:
 *      malloc(24 + (16 - 1) + sizeof(void*))
 *
 *  Here sizeof(void*) ensures we have the space to hold a pointer to the
 *  original memory returned from malloc.  (16 - 1) ensures we have enough
 *  space to pad to our requested alignment.  24 ensures we have enough memory
 *  to hold our new object (of size 24).
 *
 *  In our fictional example, this malloc returned a pointer to memory at:
 *      0x00100d53
 *  Where the upper boundary is at 0x100d82 (+0x2f)
 *
 *  This address is not aligned, we can see this because the least significant byte
 *  is 0x3, for a 16 byte aligned address we'd expect the least significant
 *  byte to be 0x0 indicating an address that is a multiple of 16.
 *
 *  To start aligning this address we first reserve space to hold a pointer to
 *  this base address:
 *
 *      uintptr_t alignedMemory = (uintptr_t)0x00100d53 + sizeof(void*);
 *                alignedMemory = 0x00100d5b;
 *
 *  We then add to that, the reserved space we've allocated to hold the
 *  original reference and then align that address to the nearest next multiple
 *  of the alignment requested.
 *
 *      alignedMemory += (16 - ((uintpr_t)0x00100d5b & (16 - 1)) & (16 - 1));
 *                       (16 - 0xb) & 15
 *      alignedMemory += 0x5
 *      alignedMemory = 0x00100d60
 *
 *  With this calculation we've now found an address with 16 byte alignment
 *
 *  We save the base of the allocated memory in the address behind the aligned
 *  block so that free can free the memory.
 *
 *     ((void**)alignedMemory)[-1] = 0x00100d53;
 *
 *  And we save the size of the entire allocated block behind that.
 *     *((size_t*)(alignedMemory - sizeof(void*) - sizeof(size_t))) = allocateSize;
 *
 * It should be noted that looking up the size, or original reference of a
 * block of memory will almost guarantee CPU cache stals - but we're not
 * optimising for that at alloc/realloc/free time.
 *
 * +----------+---------------+
 * |0x00100d53|               | < This space in memory is used to store
 * |   ...    |               |   the size of the block
 * |0x00100d58+---------------+
 * |   ...    |   0x00100d53  | < Holds the value to the base of the block
 * |0x00100d60+---------------+   of memory
 * |          |   user data   | < Holds the object we've allocated memory for
 * |          |               |   on the 16 byte boundary
 * |          |               |
 * |   ...    |               |
 * +----------+---------------+
 */
void* __aligned_malloc(size_t aSize, uint32_t aAlignment) {
    size_t allocateSize = aSize + (aAlignment - 1) + sizeof(void*) + sizeof(size_t);
    void* newMemory = malloc(allocateSize);

    if (HINT_BP_UNLIKELY(newMemory == nullptr)) {
        return nullptr;
    }

    // Align the memory (after reserving space for the original pointer (this
    // is so the existing free(3) can free the right block).
    uintptr_t alignedMemory = (uintptr_t)newMemory + sizeof(void*) + sizeof(size_t);

    // Calculate the offset required to align to the requested alignment.
    alignedMemory += (aAlignment - (alignedMemory & (aAlignment - 1))) & (aAlignment - 1);

    // Store the original pointer in the space behind the alignedmemory
    // pointer.
    ((void**)alignedMemory)[-1] = newMemory;
    *((size_t*)(alignedMemory - sizeof(void*) - sizeof(size_t))) = allocateSize;

    return (void*)alignedMemory;
}

void __aligned_free(void* aPtr) {
    free(((void**)aPtr)[-1]);
}

size_t __aligned_header_size(void* aPtr) {
    uintptr_t baseAddress = (uintptr_t)((void**)aPtr)[-1];
    return (size_t)((uintptr_t)aPtr - baseAddress);
}

size_t __aligned_alloc_size(void* aPtr) {
    return *((size_t*)((uintptr_t)aPtr - sizeof(void*) - sizeof(size_t)));
}

/// FIXME: You can't really realloc easily without holding onto the original alignment data :/
//         revisit this api
void* __aligned_realloc(void* aPtr, size_t aNewSize, uint32_t aAlignment) {
    size_t currentSize = __aligned_alloc_size(aPtr) + __aligned_header_size(aPtr);

    if (HINT_BP_UNLIKELY(aNewSize == currentSize)) {
        return aPtr;
    }

    size_t newSize =  (currentSize < aNewSize) ? aNewSize : currentSize;

    void* newMemory = __aligned_malloc(aNewSize, aAlignment);

    if (HINT_BP_UNLIKELY(newMemory == nullptr)) {
        return nullptr;
    }

    memcpy(newMemory, aPtr, newSize);
    __aligned_free(aPtr);

    return newMemory;
}

using namespace grapl;

resultv SystemMalloc::malloc(size_t aSize, uint32_t aAlignment, void** aOut) {

    *aOut = __aligned_malloc(aSize, aAlignment);

    if (HINT_BP_UNLIKELY(*aOut == nullptr)) {
        // OOM (Out of memory) condition
        return GR_ERROR_OUT_OF_MEMORY;
    }

    return GR_OK;
}

resultv SystemMalloc::realloc(void** aPtr, size_t aNewSize, uint32_t aAlignment) {

    *aPtr= __aligned_realloc(*aPtr, aNewSize, aAlignment);

    if (HINT_BP_UNLIKELY(*aPtr == nullptr)) {
        return GR_ERROR_OUT_OF_MEMORY;
    }

    return GR_OK;
}

void SystemMalloc::free(void* aPtr) {
    __aligned_free(aPtr);
}

size_t SystemMalloc::allocSize(void* aPtr) {
    return __aligned_alloc_size(aPtr);
}
