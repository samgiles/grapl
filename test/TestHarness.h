/* vim: set ts=4 sw=4 tw=79 et :*/
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#pragma once

#define GLEW_STATIC 1
#include "GL/glew.h"
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <functional>

#include "grapl.h"

#define ACCESS_ONCE(type, var) (*(volatile type*) &(var))

static uint32_t gFailCount = 0;

void _testStatusMessage(const char* status, const char* message, va_list args) {
    printf("%s | ", status);

    vprintf(message, args);

    putchar('\n');
}

void fail(const char* message, ...) {
    va_list args;
    va_start(args, message);
    _testStatusMessage("TEST-UNEXPECTED-FAIL", message, args);
    va_end(args);
    ++gFailCount;
}

void pass(const char* message, ...) {
    va_list args;
    va_start(args, message);
    _testStatusMessage("TEST-PASS", message, args);
    va_end(args);
}

int runTest(const char* name, const std::function<bool()>& f) {
    auto result = f();
    if (result) {
        pass(name);
        return 0;
    } else {
        fail(name);
        return 1;
    }
}

int runGLTest(const char* name, const std::function<bool()>& f) {
    GLFWwindow* window;
    /* Initialize the library */
    if (!glfwInit()) {
        return 1;
    }

    // Require context to support at least version 3.2
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

    // Context should only support new core functionality
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(1, 1, "test", nullptr, nullptr); // Windowed
    if (!window)
    {
        glfwTerminate();
        return 1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

    auto result = runTest(name, f);

    glfwTerminate();
    return result;
}

int runWindowsOnlyTest(const char* name, const std::function<bool()>& f) {
#ifdef WIN32
    return runTest(name, f);
#else
    return 0;
#endif
}

int runPosixOnlyTest(const char* name, const std::function<bool()>& f) {
#ifndef WIN32
    return runTest(name, f);
#else
    return 0;
#endif
}

