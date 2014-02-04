//
//  FrameBuffer.cpp
//  ModelViewer
//
//  Created by Mattias Bergström on 2014-01-30.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include "FrameBuffer.h"
#include "Constants.h"

FrameBuffer::FrameBuffer() {
    glGenFramebuffers(1, &fboId);
}

FrameBuffer::~FrameBuffer() {
    glDeleteFramebuffers(1, &fboId);
}

void FrameBuffer::attachColorTexture(std::shared_ptr<ColorAttachment> colorTexture) {
    bind();
    // Add to FBO
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + colorTexture->index, GL_TEXTURE_2D, colorTexture->textureId, 0);
    
    colorAttachments.push_back(colorTexture);
    
    updateDrawBuffers();
    
    unbind();
}

void FrameBuffer::detachColorTexture(std::shared_ptr<ColorAttachment> colorTexture) {
    //TODO: implement
    /*bind();
    // Remove from FBO
    
    // Remove from attachments list
    auto position = std::find(colorAttachments.begin(), colorAttachments.end(), colorTexture);
    if (position != colorAttachments.end()) {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + std:, GL_TEXTURE_2D, 0, 0);
        colorAttachments.erase(position);
    }
    
    updateDrawBuffers();
    
    unbind();*/
}

void FrameBuffer::updateDrawBuffers() {
    int numberOfDrawBuffers = NUM_TEXTURES;
    GLuint drawBuffers[numberOfDrawBuffers];
    for(int i = 0; i < numberOfDrawBuffers; i++) {
        drawBuffers[i] = GL_COLOR_ATTACHMENT0 + i;
    }
    
    glDrawBuffers(numberOfDrawBuffers, &drawBuffers[0]);
}

std::vector<std::shared_ptr<ColorAttachment>> FrameBuffer::getColorAttachments() {
    return colorAttachments;
}

void FrameBuffer::setDepthAttachment(std::shared_ptr<DepthAttachment> depthTexture) {
    bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthTexture->textureId, 0);
    this->depthAttachment = depthTexture;
    unbind();
}

std::shared_ptr<DepthAttachment> FrameBuffer::getDepthAttachment() {
    return depthAttachment;
}

void FrameBuffer::bindAttachments() {
    for(auto it = colorAttachments.begin(); it != colorAttachments.end(); it++) {
        (*it)->bind();
    }
    depthAttachment->bind();
}

void FrameBuffer::unbindAttachments() {
    for(auto it = colorAttachments.begin(); it != colorAttachments.end(); it++) {
        (*it)->unbind();
    }
    depthAttachment->unbind();
}

void FrameBuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, fboId);
}

void FrameBuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}




