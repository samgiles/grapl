/* vim: set ts=4 sw=4 tw=79 et :*/
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef telemetry_h__
#define telemetry_h__

#include "uv.h"
#include "stdio.h"

namespace grapl {

typedef void (*TelemetryLogger)(const char*,const char*,uint64_t);

class Telemetry final {

    private:
        const char* mName;
        uint64_t    mStartTime;
        TelemetryLogger mLogger;

    public:
        Telemetry(const char* aName, TelemetryLogger aLogger)
            : mName(aName),
              mLogger(aLogger) {
            mStartTime = uv_hrtime();
        }

        void mark(const char* aName) const {
            uint64_t timeSince = uv_hrtime() - mStartTime;
            mLogger(mName, aName, timeSince);
        }

        static void stdoutLogger(const char* aTelemetryName, const char* aMarkName, uint64_t mTime) {
            printf("%s | %s | %lfs\n", aTelemetryName, aMarkName, double(mTime) / 1000000000.0f);
        }
};

}

#endif
