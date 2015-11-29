/* vim: set ts=4 sw=4 tw=79 et :*/
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#pragma once

#define GLEW_STATIC 1
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "base/memory/malloc.h"
#include <memory>

namespace grapl {


typedef struct {
    const int   windowWidth;
    const int   windowHeight;
    const char* windowName;
    const bool  isWindowed;

} GameConfiguration;

class GraplGame {
    protected:
        bool mShouldClose;
        GLFWwindow* mWindow;
        std::shared_ptr<IMalloc> mAllocator;
    private:
        resultv initializeGraphics(const GameConfiguration& aConfig);
    public:
        GraplGame() :
            mShouldClose(false) {}

        resultv initialize(const GameConfiguration& aConfig);
        void run();

        virtual void render() = 0;
        virtual void update(float aDelta) = 0;
};

}
