/* vim: set ts=4 sw=4 tw=79 et :*/
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "GeckoProfiler.h"
#include "grapl_game.h"
#include "base/internal_logging.h"

using namespace grapl;

resultv GraplGame::initialize(const GameConfiguration& aConfig) {
    resultv rv = initializeGraphics(aConfig);

    if (GR_FAILED(rv)) {
        return rv;
    }

    return GR_OK;
}

resultv GraplGame::initializeGraphics(const GameConfiguration& aConfig) {

    glfwSetErrorCallback([](int aError, const char* aDescription) {
        ERR("GLFW: %s", aDescription);
    });

    if (glfwInit() == GL_FALSE) {
        return GR_ERROR_GL_FAILED;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    GLFWmonitor* monitor = NULL;

    if (!aConfig.isWindowed) {
        monitor = glfwGetPrimaryMonitor();
    }

    mWindow = glfwCreateWindow(
            aConfig.windowWidth,
            aConfig.windowHeight,
            aConfig.windowName,
            monitor,
            nullptr);

    if (!mWindow) {
        glfwTerminate();
        return GR_ERROR_GL_FAILED;
    }

    glfwMakeContextCurrent(mWindow);

    glewExperimental = GL_TRUE;
    glewInit();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    return GR_OK;
}

void GraplGame::run() {
    int profilerStackRoot;
    profiler_init(&profilerStackRoot);
    PROFILER_LABEL("gameloop", "run", js::ProfileEntry::Category::GRAPHICS);

    double currentTime = 0.0f;
    double lastTime = glfwGetTime();

    do {
        PROFILER_LABEL("gameloop", "tick", js::ProfileEntry::Category::GRAPHICS);
        currentTime = glfwGetTime();

        glfwPollEvents();

        update(float(currentTime - lastTime));

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Do Graphics update
        render();

        glfwSwapBuffers(mWindow);
    } while(mShouldClose || !glfwWindowShouldClose(mWindow));

    glfwTerminate();
    profiler_shutdown();
}
