/* vim: set ts=4 sw=4 tw=79 et :*/
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "base/Logging.h"
#include "gfxShader.h"
#include <GLFW/glfw3.h>
#include <vector>

bool OpenGLShader::compile() {
    if (mGLResource) {
        LOG(LOG_WARN, "Trying to recompile an already compiled shader");
        return true;
    }

    mGLResource = glCreateShader(mShaderType);
    glShaderSource(mGLResource, 1, static_cast<const GLchar**>(&mShaderSource), NULL);
    glCompileShader(mGLResource);

    GLint infoLogLength = 0;
    glGetShaderiv(mGLResource, GL_INFO_LOG_LENGTH, &infoLogLength);


    if (infoLogLength) {
        std::vector<GLchar> infoLog(infoLogLength);
        glGetShaderInfoLog(mGLResource, infoLogLength, &infoLogLength, &infoLog[0]);

        // Check compile status
        GLint compileStatus;
        glGetShaderiv(mGLResource, GL_COMPILE_STATUS, &compileStatus);

        if (compileStatus == GL_FALSE) {
            ERR("OpenGLShader::compile - Error compiling shader!");
            ERR("Program %s: %s", mShaderSource, reinterpret_cast<char*>(infoLog.data()));
            return false;
        }
    }

    return true;
}
