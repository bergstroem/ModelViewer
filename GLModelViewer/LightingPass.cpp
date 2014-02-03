//
//  LightingPass.cpp
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-02-01.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include "LightingPass.h"
#include "UnitQuad.h"

void LightingPass::init(int width, int height) {
    RenderPass::init(width, height);
    
    phong.init();
    deferredPhong.init();
    
    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(UnitQuad::CreateUnitQuad());
    unitQuad.init(mesh);
}

void LightingPass::resize(int width, int height) {
    RenderPass::resize(width, height);
}

void LightingPass::render(glm::mat4 proj, glm::mat4 view, std::vector<std::shared_ptr<SceneNode>> nodes) {
    
    buffer->bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    phong.use();
    
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        std::shared_ptr<SceneNode> node = (*it);
        phong.setMaterial(node->mesh->material);
        phong.setUniforms(proj, view, node->modelMatrix);
        
        (*it)->render();
    }
    
    buffer->unbind();
}

void LightingPass::render(glm::mat4 proj, glm::mat4 view, FrameBuffer* gBuffer) {
    //Render lighting from data in gbuffer
    
    gBuffer->bindTextures();
    
    deferredPhong.use();
    
    glDepthMask(GL_FALSE);
    
    glm::mat4 mat1 = glm::mat4(1.0f);
    deferredPhong.setUniforms(proj, view, mat1);
    
    unitQuad.render();
    
    glDepthMask(GL_TRUE);
    gBuffer->unbindTextures();
    
}
