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
    
    shadowPass.init(width, height);
    
    // Init geometry pass
    geometryPass.init(width, height);
    
    // Init deferred lighting
    auto buffer = geometryPass.getBuffer();
    deferredLightingPass.init(width, height, buffer->getDepthAttachment());
    
    passthrough.init();
    
    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(UnitQuad::CreateUnitQuad());
    screenNode.init(mesh);
    
    this->width = width;
    this->height = height;
}

void SceneRenderer::updateResolution(int width, int height) {
    // Update everything that needs to be updated when resolution changes
    
    geometryPass.resize(width, height);
    
    shadowPass.resize(width, height);
    
    auto buffer = geometryPass.getBuffer();
    deferredLightingPass.resize(width, height, buffer->getDepthAttachment());
    
    this->width = width;
    this->height = height;
}

void SceneRenderer::renderScene() {
    
    shadowPass.render(proj, view, nodes, lights[0]);
    
    // Deferred lighting
    geometryPass.render(proj, view, nodes);
    deferredLightingPass.render(proj, view, (GBuffer*)geometryPass.getBuffer(), lights);
    
    // Draw final pass to screen    
    deferredLightingPass.bindBufferTextures();
    
    passthrough.use();
    
    glDepthMask(GL_FALSE);
    
    passthrough.setUniforms(proj, view, screenNode.modelMatrix);
    
    screenNode.render();
    
    glDepthMask(GL_TRUE);
    
    deferredLightingPass. unbindBufferTextures();
}

