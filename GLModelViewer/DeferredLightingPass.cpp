//
//  DeferredLightingPass.cpp
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-02-05.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include "DeferredLightingPass.h"
#include "UnitQuad.h"

void DeferredLightingPass::init(int width, int height) {
    std::shared_ptr<DepthAttachment> depthTexture(new DepthAttachment);
    depthTexture->init(width, height);
    
    init(width, height, depthTexture);
}

void DeferredLightingPass::init(int width, int height, std::shared_ptr<DepthAttachment> depthTexture) {
    this->width = width;
    this->height = height;
    
    resultBuffer = new ColorBuffer();
    resultBuffer->init(width, height, depthTexture);
    
    deferredPhong.init();
    
    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(UnitQuad::CreateUnitQuad());
    unitQuad.init(mesh);
}

void DeferredLightingPass::resize(int width, int height) {
    std::shared_ptr<DepthAttachment> depthTexture(new DepthAttachment);
    depthTexture->init(width, height);
    
    resize(width, height, depthTexture);
}

void DeferredLightingPass::resize(int width, int height, std::shared_ptr<DepthAttachment> depthTexture) {
    this->width = width;
    this->height = height;
    
    delete resultBuffer;
    resultBuffer = new ColorBuffer();
    resultBuffer->init(width, height, depthTexture);
}

//Render lighting on geometry in gbuffer
void DeferredLightingPass::render(glm::mat4 proj, glm::mat4 view, GBuffer* gBuffer, std::vector<std::shared_ptr<Light>> lights) {
    
    resultBuffer->bind();
    glClear(GL_COLOR_BUFFER_BIT);
    glDepthMask(GL_FALSE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);
    
    gBuffer->bindAttachments();
    lights[0]->shadowTexture->bind();
    
    deferredPhong.use();
    
    glm::mat4 mat1 = glm::mat4(1.0f);
    deferredPhong.setUniforms(proj, view, mat1);
    
    for(auto it = lights.begin(); it != lights.end(); it++) {
        deferredPhong.setLight((*it)->properties);
        
        glm::vec3 position = glm::vec3(lights[0]->properties.position);
        glm::vec3 lightDir = glm::vec3(lights[0]->properties.direction);
        
        glm::mat4 biasMatrix(
                             0.5, 0.0, 0.0, 0.0,
                             0.0, 0.5, 0.0, 0.0,
                             0.0, 0.0, 0.5, 0.0,
                             0.5, 0.5, 0.5, 1.0
                             );
        
        glm::mat4 depthProjectionMatrix = glm::perspective(lights[0]->properties.angle * 2, width/(float)height, 0.1f, 50.0f);
        glm::mat4 depthViewMatrix = glm::lookAt(position, position + lightDir, glm::vec3(0,1,0));
        deferredPhong.setLightMvp(biasMatrix * depthProjectionMatrix * depthViewMatrix);

        
        unitQuad.render();
    }
    
    lights[0]->shadowTexture->unbind();
    gBuffer->unbindAttachments();
    
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
    resultBuffer->unbind();
    
}

FrameBuffer* DeferredLightingPass::getBuffer() {
    return resultBuffer;
}

void DeferredLightingPass::bindBufferTextures() {
    this->resultBuffer->bindAttachments();
}

void DeferredLightingPass::unbindBufferTextures() {
    this->resultBuffer->unbindAttachments();
}