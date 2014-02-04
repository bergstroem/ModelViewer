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

void ColorBuffer::init(int width, int height) {
    std::shared_ptr<DepthAttachment> depthTexture(new DepthAttachment);
    depthTexture->init(width, height);
    
    init(width, height, depthTexture);
}

void ColorBuffer::init(int width, int height, std::shared_ptr<DepthAttachment> depthTexture) {
    // Create and attach color texture
    std::shared_ptr<ColorAttachment> colorTexture(new ColorAttachment);
    colorTexture->init(width, height, TEXTURE_COLOR_INDEX);
    attachColorTexture(colorTexture);
    
    // Attach depth texture
    setDepthAttachment(depthTexture);
}