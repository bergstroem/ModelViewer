//
//  DepthPass.cpp
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-02-05.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include "DepthPass.h"

void DepthPass::init(int width, int height) {
    passtroughShader.init();
    
    depthBuffer = new DepthBuffer();
    depthBuffer->init(width, height);
}

void DepthPass::resize(int width, int height) {
    delete depthBuffer;
    depthBuffer = new DepthBuffer();
    depthBuffer->init(width, height);
}

void DepthPass::render(glm::mat4 proj, glm::mat4 view, std::vector<std::shared_ptr<SceneNode>> nodes) {
    depthBuffer->bind();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glDepthMask(GL_TRUE);
    passtroughShader.use();
    
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        std::shared_ptr<SceneNode> node = (*it);
        
        passtroughShader.setUniforms(proj, view, node->modelMatrix);
        
        node->render();
    }

    // TODO: Disable depth test
    glDepthMask(GL_TRUE);
    depthBuffer->unbind();
}

FrameBuffer* DepthPass::getBuffer() {
    return depthBuffer;
}

void DepthPass::bindBufferTextures() {
    depthBuffer->bindAttachments();
}

void DepthPass::unbindBufferTextures() {
    depthBuffer->unbindAttachments();
}
