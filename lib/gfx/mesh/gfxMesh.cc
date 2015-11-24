/* vim: set ts=4 sw=4 tw=79 et :*/
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "gfxMesh.h"

using namespace grapl::gfx;

void Mesh::init() {
    glGenVertexArrays(1, &mVertexArrayObject);
    glBindVertexArray(mVertexArrayObject);

    // We need to upload this vertex data to the GPU
    // 1. Register the vertex buffer object
    glGenBuffers(1, &mVertexBufferObject);

    // 2. Make the vertex buffer object the active object
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferObject);

    // 3. Copy the vertex data to the object now that it's active
    glBufferData(GL_ARRAY_BUFFER, mSize, mVertices, GL_STATIC_DRAW);

    // GL_STATIC_DRAW: The vertex data will be uploaded once and drawn many times (e.g. the world).
    // GL_DYNAMIC_DRAW: The vertex data will be changed from time to time, but drawn many times more than that.
    // GL_STREAM_DRAW: The vertex data will change almost every time it's drawn (e.g. user interface).
}
