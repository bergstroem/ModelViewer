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
    lightingPass.init(width, height);
}

void SceneRenderer::updateResolution(int width, int height) {
    // Update everything that needs to be updated when resolution changes
    
    geometryPass.resize(width, height);
    lightingPass.resize(width, height);
}

void SceneRenderer::renderScene() {
    
    // Deferred lighting
    geometryPass.render(proj, view, nodes);
    lightingPass.render(proj, view, geometryPass.buffer);
}

