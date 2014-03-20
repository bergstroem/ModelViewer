//
//  DepthAttachment.cpp
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-02-04.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include <iostream>
#include "DepthAttachment.h"
#include <glew.h>

DepthAttachment::~DepthAttachment() {
    glDeleteTextures(1, &textureId);
}

void DepthAttachment::init(int width, int height) {
    init(width, height, TEXTURE_DEPTH_INDEX);
}

void DepthAttachment::init(int width, int height, TextureIndex index) {
    this->width = width;
    this->height = height;
    this->index = index;
    
    // Generate texture
    glGenTextures(1, &textureId);
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH32F_STENCIL8, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
    glTexParameteri (GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);
    
    // Unbind when done
    glBindTexture(GL_TEXTURE_2D, 0);
}

void DepthAttachment::bind() {
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, textureId);
}

void DepthAttachment::unbind() {
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, 0);
}

