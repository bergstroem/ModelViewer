//
//  ShadowBuffer.cpp
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-02-05.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include "DepthBuffer.h"

void DepthBuffer::init(int width, int height) {
    std::shared_ptr<DepthAttachment> depthTexture(new DepthAttachment);
    depthTexture->init(width, height);
    
    init(width, height, depthTexture);
}

void DepthBuffer::init(int width, int height, std::shared_ptr<DepthAttachment> depthTexture) {
    
    setDepthAttachment(depthTexture);
    
    bind();
    glDrawBuffer(GL_NONE);
    unbind();
}