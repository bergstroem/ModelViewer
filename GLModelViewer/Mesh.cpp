//
//  Mesh.cpp
//  ModelViewer
//
//  Created by Mattias Bergström on 2014-01-22.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include <iostream>
#include "Mesh.h"

#include <glew.h>

void Mesh::init(std::size_t numVertices, Vertex* vertexData) {
    this->vertexBuffer.resize(numVertices);
    for (int i = 0; i < numVertices; i++) {
        this->vertexBuffer[i] = vertexData[i];
    }
}

void Mesh::flipNormals() {
    // Flip ALL the normals
    for(auto it = vertexBuffer.begin(); it != vertexBuffer.end(); it++) {
        (*it).normal.x *= -1;
        (*it).normal.y *= -1;
        (*it).normal.z *= -1;
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, this->bufferId);
    glBufferData(GL_ARRAY_BUFFER, this->vertexBuffer.size()*sizeof(Vertex), &(this->vertexBuffer[0]), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::loadBufferData() {
    // Create VAO to keep buffer and attribute states
    glGenVertexArrays(1, &vaoId);
    
    bind();
    
    // Create vertex and index buffer and load into GPU
    glGenBuffers(1, &(this->bufferId));
    glGenBuffers(1, &(this->indexId));
    glBindBuffer(GL_ARRAY_BUFFER, this->bufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexId);
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer.size()*sizeof(GL_UNSIGNED_INT), &(this->indexBuffer[0]), GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, this->vertexBuffer.size()*sizeof(Vertex), &(this->vertexBuffer[0]), GL_STATIC_DRAW);
    
    // Enable vertex attributes
    glEnableVertexAttribArray(SHADER_POSITION_LOCATION);
    glEnableVertexAttribArray(SHADER_NORMAL_LOCATION);
    glEnableVertexAttribArray(SHADER_COLOR_LOCATION);
    
    // Set vertex attribute pointers
    glVertexAttribPointer(SHADER_POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glVertexAttribPointer(SHADER_NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3)));
    glVertexAttribPointer(SHADER_COLOR_LOCATION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3)*2));
    
    // Unbind vao so that we dont make changes to it outside of here
    unbind();
}

void Mesh::unloadBufferData() {
    glDeleteBuffers(1, &bufferId);
    glDeleteBuffers(1, &indexId);
    glDeleteVertexArrays(1, &vaoId);
}

void Mesh::bind() {
    glBindVertexArray(vaoId);
}

void Mesh::unbind() {
    glBindVertexArray(0);
}