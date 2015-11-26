/* vim: set ts=4 sw=4 tw=79 et :*/
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "GeckoProfiler.h"

#define GLEW_STATIC 1
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "gfx/gfxShader.h"
#include "gfx/mesh/gfxMesh.h"
#include "base/telemetry.h"

#include <vector>
#include <cmath>
#include <memory>

#include <uv.h>

#include "base/memory/malloc.h"

int main(void)
{
    // Setup Profiling/Telemetry
    int stackroot;
    profiler_init(&stackroot);
    PROFILER_LABEL("startup", "main", js::ProfileEntry::Category::OTHER);

    std::unique_ptr<grapl::IMalloc> allocator(new grapl::SystemMalloc());

    uv_loop_t* eventLoop;
    allocator->malloc(sizeof(uv_loop_t), 16, (void**)&eventLoop);

    uv_loop_init(eventLoop);

    uv_run(eventLoop, UV_RUN_DEFAULT);

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

    static GLfloat vertices[] = {
     -1.0f,-1.0f,-1.0f, // triangle 1 : begin
     -1.0f,-1.0f, 1.0f,
     -1.0f, 1.0f, 1.0f, // triangle 1 : end
     1.0f, 1.0f,-1.0f, // triangle 2 : begin
     -1.0f,-1.0f,-1.0f,
     -1.0f, 1.0f,-1.0f, // triangle 2 : end
     1.0f,-1.0f, 1.0f,
     -1.0f,-1.0f,-1.0f,
     1.0f,-1.0f,-1.0f,
     1.0f, 1.0f,-1.0f,
     1.0f,-1.0f,-1.0f,
     -1.0f,-1.0f,-1.0f,
     -1.0f,-1.0f,-1.0f,
     -1.0f, 1.0f, 1.0f,
     -1.0f, 1.0f,-1.0f,
     1.0f,-1.0f, 1.0f,
     -1.0f,-1.0f, 1.0f,
     -1.0f,-1.0f,-1.0f,
     -1.0f, 1.0f, 1.0f,
     -1.0f,-1.0f, 1.0f,
     1.0f,-1.0f, 1.0f,
     1.0f, 1.0f, 1.0f,
     1.0f,-1.0f,-1.0f,
     1.0f, 1.0f,-1.0f,
     1.0f,-1.0f,-1.0f,
     1.0f, 1.0f, 1.0f,
     1.0f,-1.0f, 1.0f,
     1.0f, 1.0f, 1.0f,
     1.0f, 1.0f,-1.0f,
     -1.0f, 1.0f,-1.0f,
     1.0f, 1.0f, 1.0f,
     -1.0f, 1.0f,-1.0f,
     -1.0f, 1.0f, 1.0f,
     1.0f, 1.0f, 1.0f,
     -1.0f, 1.0f, 1.0f,
     1.0f,-1.0f, 1.0f
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

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    double lastTime = glfwGetTime();
    uint32_t nbFrames = 0;

    PROFILER_LABEL("startup", "gameloopstart", js::ProfileEntry::Category::OTHER);
    /* Loop until the user closes the window */
    do {

        double currentTime = glfwGetTime();
        nbFrames++;
        if ((currentTime - lastTime) >= 1.0f) {
            printf("%f ms/frame\r", 1000.0f/double(nbFrames));
            fflush(stdout);
            nbFrames = 0;
            lastTime += 1.0f;
        }

        /* Poll for and process events */
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }

        // Clear the screen to black
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* Render here */
        glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
    } while (!glfwWindowShouldClose(window));

    glDeleteProgram(shaderProgram);
    glfwTerminate();

    profiler_shutdown();
    uv_loop_close(eventLoop);
    allocator->free(eventLoop);
    return 0;
}
