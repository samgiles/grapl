/* vim: set ts=4 sw=4 tw=79 et :*/
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#pragma once

#include "base/internal_logging.h"
#include <uv.h>

namespace grapl {

class AsyncFile {
    private:
        uv_fs_t mOpenRequest;
        uv_fs_t mReadRequest;
        uv_buf_t mIov;
        uv_loop_t* mEventLoop;

        char mBuffer[1024];

        static void onOpen(uv_fs_t* aReq) {
            if (aReq->result >= 0) {
                AsyncFile* _this = (AsyncFile*)aReq->data;

                _this->mIov = uv_buf_init(_this->mBuffer, sizeof(mBuffer));
                uv_fs_read(_this->mEventLoop, &_this->mReadRequest, aReq->result, &_this->mIov, 1, -1, &AsyncFile::onRead);
            } else {
                // Handle error
            }
        }

        static void onRead(uv_fs_t* aReq) {
            if (aReq->result > 0) {
                AsyncFile* _this = (AsyncFile*)aReq->data;
                LOG(LOG_INFO, "Got some stuff %s\n", _this->mIov.base);
            } else {
                // Handle error
            }
        }

    public:
        AsyncFile(const char* aPath, uv_loop_t* aEventLoop) {
            // Store a reference to this object in the request data
            mOpenRequest.data = (void*)this;
            mReadRequest.data = (void*)this;

            uv_fs_open(aEventLoop, &mOpenRequest, aPath, O_RDONLY, 0, &AsyncFile::onOpen);
        }

};

}
