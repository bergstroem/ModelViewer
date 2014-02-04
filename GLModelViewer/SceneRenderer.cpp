//
//  SceneRenderer.cpp
//  ModelViewer
//
//  Created by Mattias Bergström on 2014-01-28.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include <iostream>
#include "SceneRenderer.h"
#include "BlurShader.h"


void SceneRenderer::init(int width, int height) {
    geometryPass.init(width, height);
    auto buffer = geometryPass.getBuffer();
    lightingPass.init(width, height, buffer->getDepthAttachment());
    blurPass.init(width, height);
    passthrough.init();
    
    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(UnitQuad::CreateUnitQuad());
    screenNode.init(mesh);
    
    this->width = width;
    this->height = height;
}

void SceneRenderer::updateResolution(int width, int height) {
    // Update everything that needs to be updated when resolution changes
    
    geometryPass.resize(width, height);
    auto buffer = geometryPass.getBuffer();
    lightingPass.resize(width, height, buffer->getDepthAttachment());
    blurPass.resize(width, height);
    
    this->width = width;
    this->height = height;
}

void SceneRenderer::renderScene() {
    if(!isDeferred) {
        lightingPass.render(proj, view, nodes);
    } else {
        // Deferred lighting
        geometryPass.render(proj, view, nodes);
        lightingPass.render(proj, view, (GBuffer*)geometryPass.getBuffer());
    }
    // Draw final pass to screen
    //blurPass.render(proj, view, lightingPass.getBuffer());
    
    lightingPass.bindBufferTextures();
    
    passthrough.use();
    
    glDepthMask(GL_FALSE);
    
    passthrough.setUniforms(proj, view, screenNode.modelMatrix);
    
    screenNode.render();
    
    glDepthMask(GL_TRUE);
    
    lightingPass.unbindBufferTextures();
}

