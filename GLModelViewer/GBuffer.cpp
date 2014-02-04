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

void GBuffer::init(int width, int height) {
    std::shared_ptr<DepthAttachment> depthTexture(new DepthAttachment);
    depthTexture->init(width, height);
    
    init(width, height, depthTexture);
}

void GBuffer::init(int width, int height, std::shared_ptr<DepthAttachment> depthTexture) {
    // Normal texture
    std::shared_ptr<ColorAttachment> normalTexture(new ColorAttachment);
    normalTexture->init(width, height, TEXTURE_NORMAL_INDEX);
    attachColorTexture(normalTexture);
    
    // Diffuse texture
    std::shared_ptr<ColorAttachment> diffuseTexture(new ColorAttachment);
    diffuseTexture->init(width, height, TEXTURE_DIFFUSE_INDEX);
    attachColorTexture(diffuseTexture);
    
    // Ambient texture
    std::shared_ptr<ColorAttachment> ambientTexture(new ColorAttachment);
    ambientTexture->init(width, height, TEXTURE_AMBIENT_INDEX);
    attachColorTexture(ambientTexture);
    
    // Specular texture
    std::shared_ptr<ColorAttachment> specularTexture(new ColorAttachment);
    specularTexture->init(width, height, TEXTURE_SPECULAR_INDEX);
    attachColorTexture(specularTexture);
    
    // Shininess texture
    std::shared_ptr<ColorAttachment> shininessTexture(new ColorAttachment);
    shininessTexture->init(width, height, TEXTURE_SHININESS_INDEX);
    attachColorTexture(shininessTexture);
    
    // Attach depth texture
    setDepthAttachment(depthTexture);
}
