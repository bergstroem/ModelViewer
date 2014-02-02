//
//  RenderPass.cpp
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-02-01.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include "RenderPass.h"
#include "FrameBuffer.h"

RenderPass::~RenderPass() {
    if(buffer) {
        delete buffer;
    }
}

void RenderPass::init(int width, int height) {
    buffer = new FrameBuffer();
    buffer->init(width, height);
}

void RenderPass::resize(int width, int height) {
    delete buffer;
    buffer = new FrameBuffer();
    buffer->init(width, height);
}

void RenderPass::bindBufferTextures() {
    buffer->bindTextures();
}

void RenderPass::unbindBufferTextures() {
    buffer->unbindTextures();
}
