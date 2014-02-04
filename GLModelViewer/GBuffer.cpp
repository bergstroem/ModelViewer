//
//  GBuffer.cpp
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-02-03.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include <iostream>
#include "GBuffer.h"
#include "Constants.h"


GBuffer::GBuffer() {
    this->initialized = false;
}

GBuffer::~GBuffer() {
    release();
}

/*
 * Inits the Framebuffer, can safely be called multiple times to reinitialize
 */
bool GBuffer::init(int width, int height) {
    
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
    
    GLenum DrawBuffers[NUM_TEXTURES];
    for(int i = 0; i < NUM_TEXTURES; i++) {
        this->colorTextureIDs.push_back(createTextureAttachment());
        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, colorTextureIDs[i], 0);
        
        DrawBuffers[i] = GL_COLOR_ATTACHMENT0 + i;
    }
    
    createDepthBuffer();
    
    glDrawBuffers(NUM_TEXTURES, &DrawBuffers[0]);
    
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

bool GBuffer::init(int width, int height, unsigned int depthTexId) {
    // If the framebuffer already was initialized, release it.
    if(initialized) {
        release();
    }
    
    this->width = width;
    this->height = height;
    
    glGenFramebuffers(1, &fbID);
    this->bind();
    
    GLenum DrawBuffers[NUM_TEXTURES];
    for(int i = 0; i < NUM_TEXTURES; i++) {
        this->colorTextureIDs.push_back(createTextureAttachment());
        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, colorTextureIDs[i], 0);
        
        DrawBuffers[i] = GL_COLOR_ATTACHMENT0 + i;
    }
    
    this->depthTextureID = depthTexId;
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthTexId, 0);
    
    glDrawBuffers(NUM_TEXTURES, &DrawBuffers[0]);
    
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

void GBuffer::release() {
    // Only delete from GPU if actually initialized
    if(initialized) {
        if(!colorTextureIDs.empty()) {
            std::cout << "Goodbye from GBuffer " << this << std::endl;
            glDeleteTextures((int)colorTextureIDs.size(), &(colorTextureIDs[0]));
        }
    }
}

void GBuffer::bindTextures() {
    // Bind color textures
    for(int i = 0; i < NUM_TEXTURES; i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, colorTextureIDs[i]);
    }
    
    //Bind depth
    glActiveTexture(GL_TEXTURE0 + TEXTURE_DEPTH_INDEX);
    glBindTexture(GL_TEXTURE_2D, depthTextureID);
}

void GBuffer::unbindTextures() {
    
    // unbind color textures
    for(int i = 0; i < NUM_TEXTURES; i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    //unbind depth
    glActiveTexture(GL_TEXTURE0 + TEXTURE_DEPTH_INDEX);
    glBindTexture(GL_TEXTURE_2D, 0);
}