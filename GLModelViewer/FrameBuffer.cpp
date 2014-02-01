//
//  FrameBuffer.cpp
//  ModelViewer
//
//  Created by Mattias Bergström on 2014-01-30.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include <iostream>
#include "FrameBuffer.h"
#include "Constants.h"

static const GLfloat g_quad_vertex_buffer_data[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    1.0f,  1.0f, 0.0f,
};

FrameBuffer::FrameBuffer() {
    this->initialized = false;
}

FrameBuffer::~FrameBuffer() {
    release();
}

/*
 * Inits the Framebuffer, can safely be called multiple times to reinitialize
 */
bool FrameBuffer::init(int width, int height) {
    
    // If the framebuffer already was initialized, release it.
    if(initialized) {
        release();
    }
    
    this->initialized = true;
    this->width = width;
    this->height = height;
    
    glGenFramebuffers(1, &fbID);
    this->bind();
    
    // Create buffers for all vertex data
    // TODO: Maybe add the possibility to create frame buffers that dont have all the buffers
    
    GLenum DrawBuffers[NUM_TEXTURE_INDICES];
    for(int i = 0; i < NUM_TEXTURE_INDICES; i++) {
        this->colorTextureIDs.push_back(createTextureAttachment());
        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, colorTextureIDs[i], 0);
        
        DrawBuffers[i] = GL_COLOR_ATTACHMENT0 + i;
    }
    createDepthBuffer();
    
    
    glDrawBuffers(NUM_TEXTURE_INDICES, &DrawBuffers[0]); // "2" is the size of DrawBuffers
    
    // Always check that our framebuffer is ok
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        this->unbind();
        return false;
    } else {
        this->unbind();
        return true;
    }
}

void FrameBuffer::release() {
    // Only delete from GPU if actually initialized
    if(initialized) {
        if(!colorTextureIDs.empty()) {
            glDeleteTextures((int)colorTextureIDs.size(), &(colorTextureIDs[0]));
        }
        glDeleteRenderbuffers(1, &depthBufferID);
        glDeleteFramebuffers(1, &fbID);
    }
}

// TODO: rename to Texture(s) and create multiple textures
unsigned int FrameBuffer::createTextureAttachment() {
    unsigned int texID;
    glGenTextures(1, &texID);
    
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, this->width, this->height, 0, GL_RGB, GL_FLOAT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    return texID;
}

void FrameBuffer::createDepthBuffer() {
    glGenRenderbuffers(1, &depthBufferID);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBufferID);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, this->width, this->height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBufferID);
}

void FrameBuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, fbID);
}

void FrameBuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::bindTextures() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, colorTextureIDs[0]);
    
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, colorTextureIDs[1]);
}

void FrameBuffer::unbindTextures() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);
}


