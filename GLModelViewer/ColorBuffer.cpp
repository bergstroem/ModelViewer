//
//  ColorBuffer.cpp
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-02-03.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include "ColorBuffer.h"
#include <iostream>
#include "Constants.h"

ColorBuffer::ColorBuffer() {
    this->initialized = false;
}

ColorBuffer::~ColorBuffer() {
    release();
}

/*
 * Inits the Framebuffer, can safely be called multiple times to reinitialize
 */
bool ColorBuffer::init(int width, int height) {
    
    // If the framebuffer already was initialized, release it.
    if(initialized) {
        release();
    }
    
    this->width = width;
    this->height = height;
    
    glGenFramebuffers(1, &fbID);
    this->bind();
    
    // Create buffers for all vertex data
    // TODO: Maybe add the possibility to create frame buffers that dont have all the buffers
    
    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    
    colorTextureID = createTextureAttachment();
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, colorTextureID, 0);
    
    createDepthBuffer();
    
    glDrawBuffers(1, &DrawBuffers[0]);
    
    // Always check that our framebuffer is ok
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        this->unbind();
        throw "Framebuffer not complete!";
    } else {
        this->unbind();
        this->initialized = true;
        return true;
    }
}

bool ColorBuffer::init(int width, int height, unsigned int depthTexId) {
    // If the framebuffer already was initialized, release it.
    if(initialized) {
        release();
    }
    
    this->width = width;
    this->height = height;
    
    glGenFramebuffers(1, &fbID);
    this->bind();
    
    // Create buffers for all vertex data
    // TODO: Maybe add the possibility to create frame buffers that dont have all the buffers
    
    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    
    colorTextureID = createTextureAttachment();
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, colorTextureID, 0);
    
    this->depthTextureID = depthTexId;
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthTexId, 0);
    
    glDrawBuffers(1, &DrawBuffers[0]);
    
    // Always check that our framebuffer is ok
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        this->unbind();
        throw "Framebuffer not complete!";
    } else {
        this->unbind();
        this->initialized = true;
        return true;
    }
}

void ColorBuffer::release() {
    // Only delete from GPU if actually initialized
    if(initialized) {
        std::cout << "Goodbye from ColorBuffer " << this << std::endl;
        glDeleteTextures(1, &colorTextureID);
    }
}

void ColorBuffer::bindTextures() {
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, colorTextureID);

    //Bind depth
    glActiveTexture(GL_TEXTURE0 + TEXTURE_DEPTH_INDEX);
    glBindTexture(GL_TEXTURE_2D, depthTextureID);
}

void ColorBuffer::unbindTextures() {
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);

    //unbind depth
    glActiveTexture(GL_TEXTURE0 + TEXTURE_DEPTH_INDEX);
    glBindTexture(GL_TEXTURE_2D, 0);
}
