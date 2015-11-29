/* vim: set ts=4 sw=4 tw=79 et :*/
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "TestHarness.h"
#include <memory>
#include "grapl.h"

int main(int argc, char* argv[]) {

    int rv = 0;

    rv +=
    runGLTest("Valid fragment shader compilation", []() {
        const char* fragShaderSource =
            "#version 150 core\n"
            "in vec3 Color;"
            "out vec4 outColor;"
            "void main() {"
            "  outColor = vec4(Color, 1.0);"
            "}";

        std::unique_ptr<OpenGLShader>
            fragShader(new OpenGLShader(fragShaderSource, GL_FRAGMENT_SHADER));

        return fragShader->compile();
    });

    rv +=
    runGLTest("Invalid fragment shader compilation should fail", []() {
        const char* fragShaderSource =
            "not a shader";

        std::unique_ptr<OpenGLShader>
            fragShader(new OpenGLShader(fragShaderSource, GL_FRAGMENT_SHADER));

        return !fragShader->compile();
    });

    rv +=
    runGLTest("Valid vertex shader compilation", []() {
        const char* vertexShaderSource =
            "#version 150 core\n"
            "in vec2 position;"
            "void main() {"
            "  gl_Position = vec4(position, 0.0, 1.0);"
            "}";
        std::unique_ptr<OpenGLShader>
            vertShader(new OpenGLShader(vertexShaderSource, GL_VERTEX_SHADER));

        return vertShader->compile();
    });

    rv +=
    runGLTest("Invalid vertex shader compilation should fail", []() {
        const char* vertexShaderSource =
            "not a shader";

        std::unique_ptr<OpenGLShader>
            vertShader(new OpenGLShader(vertexShaderSource, GL_VERTEX_SHADER));

        return !vertShader->compile();
    });

    return rv;
}
