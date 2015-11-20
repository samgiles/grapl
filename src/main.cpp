/* vim: set ts=4 sw=4 tw=79 et :*/
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include <iostream>

#define GLEW_STATIC 1
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "gfx/gfxShader.h"

#include <vector>
#include <cmath>
#include <memory>


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()) {
        return -1;
    }

    // Require context to support at least version 3.2
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

    // Context should only support new core functionality
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(800, 600, "Open GL", nullptr, nullptr); // Windowed
    /* Create a full screen mode window and its OpenGL context */
    //window = glfwCreateWindow(800, 600, "Open GL", glfwGetPrimaryMonitor(), nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

    float vertices[] = {
        0.0f, 0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f
    };

    GLuint vertexArrayObject;
    glGenVertexArrays(1, &vertexArrayObject);

    glBindVertexArray(vertexArrayObject);


    // We need to upload this vertex data to the GPU
    // 1. Register the vertex buffer object
    GLuint vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);

    // 2. Make the vertex buffer object the active object
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

    // 3. Copy the vertex data to the object now that it's active
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // GL_STATIC_DRAW: The vertex data will be uploaded once and drawn many times (e.g. the world).
    // GL_DYNAMIC_DRAW: The vertex data will be changed from time to time, but drawn many times more than that.
    // GL_STREAM_DRAW: The vertex data will change almost every time it's drawn (e.g. user interface).

    // Compile shaders
    const GLchar* vertShader =
        "#version 150 core\n"
        "in vec2 position;"
        "in vec3 color;"
        "out vec3 Color;"
        "void main() {"
        "   Color = color;"
        "   gl_Position = vec4(position, 0.0, 1.0);"
        "}";

    const GLchar* fragShader =
        "#version 150 core\n"
        "in vec3 Color;"
        "out vec4 outColor;"
        "void main() {"
        "  outColor = vec4(Color, 1.0);"
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
                        5 * sizeof(float),
                        /* The offset */
                        0);

    GLint colorAttribute = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colorAttribute);
    glVertexAttribPointer(colorAttribute, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(2*sizeof(float)));

    /* The stride is the number of bytes between each position attribute in the
     * array, the value of 0 means there is no data between each vertex
     *
     * The offset is the value from the start of the array where the position
     * begins
     */



    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Poll for and process events */
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }

        // Clear the screen to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /* Render here */
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
    }

    glDeleteProgram(shaderProgram);
    glDeleteBuffers(1, &vertexBufferObject);

    glDeleteVertexArrays(1, &vertexArrayObject);
    glfwTerminate();
    return 0;
}
