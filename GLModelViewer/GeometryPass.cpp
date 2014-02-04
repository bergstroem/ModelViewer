//
//  GeometryPass.cpp
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-02-01.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include <iostream>
#include "GeometryPass.h"
#include <vector>
#include <memory>
#include "SceneNode.h"

void GeometryPass::init(int width, int height) {
    geometryShader.init();
    
    resultBuffer = new GBuffer();
    resultBuffer->init(width, height);
}

void GeometryPass::resize(int width, int height) {
    
    delete resultBuffer;
    resultBuffer = new GBuffer();
    resultBuffer->init(width, height);
}

void GeometryPass::render(glm::mat4 proj, glm::mat4 view, std::vector<std::shared_ptr<SceneNode> > nodes) {
    resultBuffer->bind();
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    geometryShader.use();
    
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        std::shared_ptr<SceneNode> node = (*it);
        
        geometryShader.setMaterial(node->mesh->material);
        geometryShader.setUniforms(proj, view, node->modelMatrix);
        
        (*it)->render();
    }
    
    resultBuffer->unbind();
}

FrameBuffer* GeometryPass::getBuffer() {
    return resultBuffer;
}

void GeometryPass::bindBufferTextures() {
    this->resultBuffer->bindAttachments();
}

void GeometryPass::unbindBufferTextures() {
    this->resultBuffer->unbindAttachments();
}