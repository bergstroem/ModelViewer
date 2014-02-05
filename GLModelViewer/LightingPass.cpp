//
//  LightingPass.cpp
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-02-01.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include "LightingPass.h"
#include "UnitQuad.h"
#include <iostream>

void LightingPass::init(int width, int height) {
    std::shared_ptr<DepthAttachment> depthTexture(new DepthAttachment);
    depthTexture->init(width, height);
    
    init(width, height, depthTexture);
}

void LightingPass::init(int width, int height, std::shared_ptr<DepthAttachment> depthTexture) {
    resultBuffer = new ColorBuffer();
    resultBuffer->init(width, height, depthTexture);
    
    phong.init();
}

void LightingPass::resize(int width, int height) {
    std::shared_ptr<DepthAttachment> depthTexture(new DepthAttachment);
    depthTexture->init(width, height);
    
    resize(width, height, depthTexture);
}

void LightingPass::resize(int width, int height, std::shared_ptr<DepthAttachment> depthTexture) {
    
    delete resultBuffer;
    resultBuffer = new ColorBuffer();
    resultBuffer->init(width, height, depthTexture);
}

void LightingPass::render(glm::mat4 proj, glm::mat4 view, std::vector<std::shared_ptr<SceneNode>> nodes, std::vector<std::shared_ptr<Light>> lights) {
    
    resultBuffer->bind();
    
    // Disable depth write
    if(!shouldWriteDepth) {
        glDepthMask(GL_FALSE);
        glClear(GL_COLOR_BUFFER_BIT);
    } else {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);
    
    phong.use();
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        std::shared_ptr<SceneNode> node = (*it);
        phong.setUniforms(proj, view, node->modelMatrix);
        phong.setMaterial(node->mesh->material);
        
        for(auto it = lights.begin(); it != lights.end(); it++) {
            phong.setLight(*(*it));
            
            node->render();
        }
    }
    
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
    
    resultBuffer->unbind();
}


FrameBuffer* LightingPass::getBuffer() {
    return resultBuffer;
}

void LightingPass::bindBufferTextures() {
    this->resultBuffer->bindAttachments();
}

void LightingPass::unbindBufferTextures() {
    this->resultBuffer->unbindAttachments();
}