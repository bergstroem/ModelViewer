//
//  HDRPass.cpp
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-03-20.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include "HDRPass.h"
#include "UnitQuad.h"

void HDRPass::init(int width, int height) {
    std::shared_ptr<DepthAttachment> depthTexture(new DepthAttachment);
    depthTexture->init(width, height);
    
    init(width, height, depthTexture);
}

void HDRPass::init(int width, int height, std::shared_ptr<DepthAttachment> depthTexture) {
    this->width = width;
    this->height = height;
    
    resultBuffer = new ColorBuffer();
    resultBuffer->init(width, height, depthTexture);
    
    toneMapping.init();
    passthrough.init();
    
    bloomPass.init(width, height);
    
    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(UnitQuad::CreateUnitQuad());
    unitQuad.init(mesh);
}

void HDRPass::resize(int width, int height) {
    std::shared_ptr<DepthAttachment> depthTexture(new DepthAttachment);
    depthTexture->init(width, height);
    
    resize(width, height, depthTexture);
}

void HDRPass::resize(int width, int height, std::shared_ptr<DepthAttachment> depthTexture) {
    this->width = width;
    this->height = height;
    
    delete resultBuffer;
    resultBuffer = new ColorBuffer();
    resultBuffer->init(width, height, depthTexture);
    
    bloomPass.resize(width, height);
}

void HDRPass::render(glm::mat4 proj, glm::mat4 view, ColorBuffer* buffer, float exposure) {
    
    resultBuffer->bind();
    glDepthMask(GL_FALSE);
    glClear(GL_COLOR_BUFFER_BIT);
    
    buffer->bindAttachments();
    
    toneMapping.use();
    toneMapping.setUniforms(glm::mat4(1.0), glm::mat4(1.0), glm::mat4(1.0));
    toneMapping.setExposure(exposure);
    
    unitQuad.render();
    
    buffer->unbindAttachments();
    glDepthMask(GL_TRUE);
    resultBuffer->unbind();
    
    // Render image to screen
    resultBuffer->bindAttachments();
    
    passthrough.use();
    passthrough.setUniforms(proj, view, glm::mat4(1.0));
    
    unitQuad.render();
    
    resultBuffer->unbindAttachments();
    
    
    bloomPass.render(proj, view, resultBuffer);
    
    glDepthMask(GL_FALSE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);
    
    bloomPass.getBuffer()->bindAttachments();
    
    passthrough.use();
    passthrough.setUniforms(proj, view, glm::mat4(1.0));
    
    unitQuad.render();
    
    bloomPass.getBuffer()->unbindAttachments();
    
    glDepthMask(GL_FALSE);
    glDisable(GL_BLEND);
    
}

FrameBuffer* HDRPass::getBuffer() {
    return resultBuffer;
}

void HDRPass::bindBufferTextures() {
    this->resultBuffer->bindAttachments();
}

void HDRPass::unbindBufferTextures() {
    this->resultBuffer->unbindAttachments();
}
