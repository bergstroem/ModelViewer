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
#include <GLFW/glfw3.h>

void SceneRenderer::init(int width, int height) {
    
    // Init geometry pass
    geometryPass.init(width, height);
    
    // Init deferred lighting
    auto buffer = geometryPass.getBuffer();
    deferredLightingPass.init(width, height, buffer->getDepthAttachment());
    
    toneMapping.init();
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
    deferredLightingPass.resize(width, height, buffer->getDepthAttachment());
    
    this->width = width;
    this->height = height;
}

void SceneRenderer::renderScene() {
    
    // Deferred lighting
    geometryPass.render(proj, view, nodes);
    deferredLightingPass.render(proj, view, (GBuffer*)geometryPass.getBuffer(), nodes, lights);
    
    // Draw final pass to screen
    deferredLightingPass.bindBufferTextures();
    
    toneMapping.use();
    
    glDepthMask(GL_FALSE);
    
    toneMapping.setUniforms(proj, view, screenNode.modelMatrix);
    toneMapping.setExposure(exposure);
    
    screenNode.render();
    
    glDepthMask(GL_TRUE);
    
    deferredLightingPass.unbindBufferTextures();
}

