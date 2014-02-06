//
//  ShadowPass.cpp
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-02-05.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include <iostream>
#include "ShadowPass.h"

void ShadowPass::render(glm::mat4 proj, glm::mat4 view, std::vector<std::shared_ptr<SceneNode>> nodes, std::vector<std::shared_ptr<Light>> lights) {
    shadowBuffer->bind();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glDepthMask(GL_TRUE);
    shader.use();
    
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        std::shared_ptr<SceneNode> node = (*it);
        
        // Create matrices from light, for now just one light
        glm::vec3 position = glm::vec3(lights[0]->properties.position);
        glm::vec3 lightDir = glm::vec3(lights[0]->properties.direction);
        
        glm::mat4 depthProjectionMatrix = glm::perspective(lights[0]->properties.angle * 2, width/(float)height, 0.1f, 50.0f);
        glm::mat4 depthViewMatrix = glm::lookAt(position, position + lightDir, glm::vec3(0,1,0));
        shader.setUniforms(depthProjectionMatrix, depthViewMatrix, node->modelMatrix);
        
        node->render();
    }
    
    // TODO: Disable depth test
    glDepthMask(GL_TRUE);
    shadowBuffer->unbind();
}

void ShadowPass::init(int width, int height) {
    shadowBuffer = new DepthBuffer();
    shadowBuffer->init(width, height);
    
    this->width = width;
    this->height = height;
    
    shader.init();
}

void ShadowPass::resize(int width, int height) {
    delete shadowBuffer;
    shadowBuffer = new DepthBuffer();
    shadowBuffer->init(width, height);
    
    this->width = width;
    this->height = height;
}

FrameBuffer* ShadowPass::getBuffer() {
    return shadowBuffer;
}

void ShadowPass::bindBufferTextures() {
    shadowBuffer->bindAttachments();
}

void ShadowPass::unbindBufferTextures() {
    shadowBuffer->unbindAttachments();
}