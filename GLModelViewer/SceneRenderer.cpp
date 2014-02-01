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
    //blurPass.init(width, height);
    buf.init(width, height);
}

void SceneRenderer::updateResolution(int width, int height) {
    // Update everything that needs to be updated when resolution changes
    //blurPass.resize(width, height);
}

void SceneRenderer::renderScene() {
    //blurPass.render(proj, view, nodes);
    
    //buf.bind();
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderNodes();
    //buf.unbind();
}

void SceneRenderer::renderNodes() {
    for (auto it = this->nodes.begin(); it != this->nodes.end(); it++) {
        (*it)->render(proj, view);
    }
}