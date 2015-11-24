/* vim: set ts=4 sw=4 tw=79 et :*/
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef gfxMesh_h__
#define gfxMesh_h__

#include "GL/glew.h"

namespace grapl { namespace gfx {

/// Holds render data
class Mesh {

    private:
        GLuint mVertexArrayObject;
        GLuint mVertexBufferObject;
        GLfloat* mVertices;
        uint64_t mSize;

    public:
        Mesh(GLfloat* aVertices, uint64_t aSize)
            : mVertices(aVertices),
              mSize(aSize),
              mVertexArrayObject(0),
              mVertexBufferObject(0) {}

        ~Mesh() {
            glDeleteBuffers(1, &mVertexBufferObject);
            glDeleteVertexArrays(1, &mVertexArrayObject);
        }

        void init();

};

}
}

#endif // gfxMesh_h__
