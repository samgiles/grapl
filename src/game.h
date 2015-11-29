/* vim: set ts=4 sw=4 tw=79 et :*/
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#pragma once

#include "grapl.h"

class DemoGame final : public grapl::GraplGame {

    public:
        DemoGame() : grapl::GraplGame() {
        }

        void render();
        void update(float aDelta);
};
