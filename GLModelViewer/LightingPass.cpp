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
    deferredPhong.init();
    
    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(UnitQuad::CreateUnitQuad());
    unitQuad.init(mesh);
}

void LightingPass::resize(int width, int height) {
    std::shared_ptr<DepthAttachment> depthTexture(new DepthAttachment);
    depthTexture->init(width, height);
    
    init(width, height, depthTexture);
}

void LightingPass::resize(int width, int height, std::shared_ptr<DepthAttachment> depthTexture) {
    
    
    delete resultBuffer;
    resultBuffer = new ColorBuffer();
    resultBuffer->init(width, height);
}

void LightingPass::render(glm::mat4 proj, glm::mat4 view, std::vector<std::shared_ptr<SceneNode>> nodes) {
    
    resultBuffer->bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    phong.use();
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        std::shared_ptr<SceneNode> node = (*it);
        phong.setMaterial(node->mesh->material);
        phong.setUniforms(proj, view, node->modelMatrix);
        
        (*it)->render();
    }
    
    resultBuffer->unbind();
}

void LightingPass::render(glm::mat4 proj, glm::mat4 view, GBuffer* gBuffer) {
    //Render lighting from data in gbuffer
    
    // Dont write to the depth buffer on light pass
    glDepthMask(GL_FALSE);
    
    resultBuffer->bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    gBuffer->bindAttachments();
    
    deferredPhong.use();
    
    glm::mat4 mat1 = glm::mat4(1.0f);
    deferredPhong.setUniforms(proj, view, mat1);
    
    unitQuad.render();
    
    gBuffer->unbindAttachments();
    
    resultBuffer->unbind();
    glDepthMask(GL_TRUE);
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