/* vim: set ts=4 sw=4 tw=79 et :*/
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "GeckoProfiler.h"

#define GLEW_STATIC 1
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "grapl.h"
#include "game.h"

#include <vector>
#include <cmath>
#include <memory>

int main(void)
{
    DemoGame game = DemoGame();

    resultv rv = game.initialize({
        800, // Width
        600, // Height
        "Open GL", // Window name
        true // Windowed?
    });

    if (GR_FAILED(rv)) {
        ERR("Failed to initialize %d", rv);
        return 1;
    }


    static GLfloat vertices[] = {
     -1.0f,-1.0f,-1.0f, // triangle 1 : begin
     -1.0f,-1.0f, 1.0f,
     -1.0f, 1.0f, 1.0f // triangle 1 : end
    };

    grapl::gfx::Mesh mesh = grapl::gfx::Mesh(vertices, sizeof(vertices));
    mesh.init();

    // Compile shaders
    const GLchar* vertShader =
        "#version 150 core\n"
        "in vec2 position;"
        "void main() {"
        "   gl_Position = vec4(position, 0.0, 1.0);"
        "}";

    const GLchar* fragShader =
        "#version 150 core\n"
        "out vec4 outColor;"
        "void main() {"
        "  outColor = vec4(1.0, 1.0, 1.0, 1.0);"
        "}";

    // TODO: Error handling

    std::unique_ptr<OpenGLShader> vertexShaderObject(new OpenGLShader(vertShader, GL_VERTEX_SHADER));
    std::unique_ptr<OpenGLShader> fragmentShaderObject(new OpenGLShader(fragShader, GL_FRAGMENT_SHADER));

    vertexShaderObject->compile();
    fragmentShaderObject->compile();
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShaderObject->mGLResource);
    glAttachShader(shaderProgram, fragmentShaderObject->mGLResource);

    // Bind the output to the correct buffer (should happen before linking)
    glBindFragDataLocation(shaderProgram, 0, "outColor");

    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // Get a reference to the "position" input of the vertex shader
    GLint positionAttribute = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(positionAttribute);

    glVertexAttribPointer(positionAttribute,
                        /* number of inputs/components in vec */
                        2,
                        /* Type of each component */
                        GL_FLOAT,
                        /* Normalize between -1.0 and 1.0? */
                        GL_FALSE,
                        /* The "stride" */
                        0,
                        /* The offset */
                        0);


    /* The stride is the number of bytes between each position attribute in the
     * array, the value of 0 means there is no data between each vertex
     *
     * The offset is the value from the start of the array where the position
     * begins
     */

    game.run();

    glDeleteProgram(shaderProgram);
    return 0;
}
