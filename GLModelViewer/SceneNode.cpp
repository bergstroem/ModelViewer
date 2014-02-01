//
//  Model.cpp
//  ModelViewer
//
//  Created by Mattias Bergström on 2014-01-28.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include <iostream>
#include "SceneNode.h"


SceneNode::SceneNode() {
    
}

SceneNode::~SceneNode() {
    glDeleteVertexArrays(1, &vao);
}

void SceneNode::init(std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shaderProgram) {
    this->mesh = mesh;
    this->shaderProgram = shaderProgram;
    
    glGenVertexArrays(1, &vao);
    
    bindVAO();
    
    //Load and bind mesh so that it gets saved in the VAO state
    mesh->loadBufferData();
    mesh->bind();
    
    // Init attributes that gets saved in the VAO state
    shaderProgram->setupAttributes();
    
    unbindVAO();
}

void SceneNode::render(glm::mat4 proj, glm::mat4 view) {
    
    modelMatrix = glm::translate(glm::mat4(1.0f), position);
    modelMatrix = modelMatrix * rotation;
    
    bindVAO();
    
    // Prepare shader for rendering
    shaderProgram->use();
    shaderProgram->setUniforms(proj, view, modelMatrix);
    
    // Render scene node
    glDrawElements(GL_TRIANGLES, (int)this->mesh->indexBuffer.size(), GL_UNSIGNED_INT, (GLvoid*)((char*)NULL));
    
    unbindVAO();
}

void SceneNode::bindVAO() {
    glBindVertexArray(vao);
}

void SceneNode::unbindVAO() {
    glBindVertexArray(0);
}


