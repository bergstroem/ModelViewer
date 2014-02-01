//
//  Mesh.cpp
//  ModelViewer
//
//  Created by Mattias Bergström on 2014-01-22.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include <iostream>
#include "Mesh.h"

void Mesh::init(std::size_t numVertices, Vertex* vertexData) {
    this->vertexBuffer.resize(numVertices);
    for (int i = 0; i < numVertices; i++) {
        this->vertexBuffer[i] = vertexData[i];
    }
}

Mesh::~Mesh() {
    // Unload from buffer
    glDeleteBuffers(1, &bufferId);
    glDeleteBuffers(1, &indexId);
}

void Mesh::loadBufferData() {
    // Create vertex and index buffer and load into GPU
    glGenBuffers(1, &(this->bufferId));
    glBindBuffer(GL_ARRAY_BUFFER, this->bufferId);
    glBufferData(GL_ARRAY_BUFFER, this->vertexBuffer.size()*sizeof(Vertex), &(this->vertexBuffer[0]), GL_STATIC_DRAW);
    
    glGenBuffers(1, &(this->indexId));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer.size()*sizeof(GL_UNSIGNED_INT), &(this->indexBuffer[0]), GL_STATIC_DRAW);
    
    unbind();
}

void Mesh::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, this->bufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexId);
}

void Mesh::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}