/* vim: set ts=4 sw=4 tw=79 et :*/
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#pragma once

#include "base/internal_logging.h"
#include "base/memory/malloc.h"
#include <uv.h>
#include <memory>

namespace grapl { namespace async {

/**
 * A worker represents a remote event loop.
 */
class Worker final {
    protected:
        const char* mName;
        uv_thread_t mThreadId;
        bool mInitialized;
        std::shared_ptr<IMalloc> mAllocator;

        static void runWorker(void* aArg) {
            if (aArg != nullptr) {
                ((Worker*)aArg)->_run();
            } else {
                ERR("Worker - failed to start. A nullptr was passed as an arugment");
            }
        }

        void _run();

        static void onIdle(uv_idle_t* aIdle) {
            Worker* _this = (Worker*)aIdle->data;
            LOG(LOG_INFO, "[%s] Idling..", _this->mName);
        }

    public:
        Worker(const char* aName, std::shared_ptr<IMalloc> aAllocator) : mName(aName), mInitialized(false), mAllocator(aAllocator) {}

        void start();
        void join();
};

}}
