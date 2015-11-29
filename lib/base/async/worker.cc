/* vim: set ts=4 sw=4 tw=79 et :*/
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "worker.h"


using namespace grapl::async;

void Worker::_run() {
    uv_loop_t* eventLoop;
    mAllocator->malloc(sizeof(uv_loop_t), 16, (void**)&eventLoop);
    uv_loop_init(eventLoop);

    uv_run(eventLoop, UV_RUN_DEFAULT);
    uv_loop_close(eventLoop);
    mAllocator->free(eventLoop);
}

void Worker::start() {
    // Initialize new thread
    if (!mInitialized) {
        mInitialized = true;
        uv_thread_create(&mThreadId, &Worker::runWorker, this);
    }
}

void Worker::join() {
    uv_thread_join(&mThreadId);
}
