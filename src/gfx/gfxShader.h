/* vim: set ts=4 sw=4 tw=79 et :*/
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef gfxShader_h__
#define gfxShader_h__

#include "GL/glew.h"

class OpenGLShader {
    public:

        /// The OpenGL Resource ID
        GLuint mGLResource;

        /// True if the shader compiled successfully
        bool mSuccessfullyCompiled;

        OpenGLShader(const char* aShaderSource, GLenum aShaderType) :
            mSuccessfullyCompiled(false),
            mShaderSource(aShaderSource),
            mShaderType(aShaderType),
			mGLResource(0) {
        }

        ~OpenGLShader() {
            if (mGLResource) {
                glDeleteShader(mGLResource);
            }
        }

        bool compile();
    private:
        const char* mShaderSource;
        GLenum mShaderType;
};
#endif

