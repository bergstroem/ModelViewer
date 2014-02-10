//
//  ShadowPass.cpp
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-02-05.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include <iostream>
#include "ShadowPass.h"
#include "DepthAttachment.h"
#include "Constants.h"

void ShadowPass::render(glm::mat4 proj, glm::mat4 view, std::vector<std::shared_ptr<SceneNode>> nodes, std::shared_ptr<Light> light) {
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
    shadowBuffer->bind();
    glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    shader.use();
    
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        std::shared_ptr<SceneNode> node = (*it);
        
        // Create matrices from light, for now just one light
        glm::vec3 position = glm::vec3(light->properties.position);
        glm::vec3 lightDir = glm::vec3(light->properties.direction);
        
        glm::mat4 depthProjectionMatrix = glm::perspective(light->properties.angle * 2, width/(float)height, 0.1f, 50.0f);
        glm::mat4 depthViewMatrix = glm::lookAt(position, position + lightDir, glm::vec3(0,1,0));
        shader.setUniforms(depthProjectionMatrix, depthViewMatrix, node->modelMatrix);
        
        node->render();
    }
    
    light->shadowTexture = shadowBuffer->getDepthAttachment();
    
    shadowBuffer->unbind();
}

void ShadowPass::init(int width, int height) {
    std::shared_ptr<DepthAttachment> depth(new DepthAttachment);
    depth->init(width, height, TEXTURE_SHADOW0_INDEX);
    
    shadowBuffer = new DepthBuffer();
    shadowBuffer->init(width, height, depth);
    
    this->width = width;
    this->height = height;
    
    shader.init();
}

void ShadowPass::resize(int width, int height) {
    std::shared_ptr<DepthAttachment> depth(new DepthAttachment);
    depth->init(width, height, TEXTURE_SHADOW0_INDEX);
    
    delete shadowBuffer;
    shadowBuffer = new DepthBuffer();
    shadowBuffer->init(width, height, depth);
    
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