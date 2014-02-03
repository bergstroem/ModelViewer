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
}

void SceneNode::init(std::shared_ptr<Mesh> mesh) {
    this->mesh = mesh;
}

void SceneNode::render() {
    
    modelMatrix = glm::translate(glm::mat4(1.0f), position);
    modelMatrix = modelMatrix * rotation;
    
    mesh->bind();
    
    // Render scene node
    glDrawElements(GL_TRIANGLES, (int)this->mesh->indexBuffer.size(), GL_UNSIGNED_INT, (GLvoid*)((char*)NULL));
    
    mesh->unbind();
}


