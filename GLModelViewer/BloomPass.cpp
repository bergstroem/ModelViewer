//
//  BloomPass.cpp
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-03-20.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include "BloomPass.h"
#include "UnitQuad.h"
#include "BlurShader.h"


BloomPass::~BloomPass() {
    if(blurBuffer) {
        delete blurBuffer;
    }
    if(resultBuffer) {
        delete resultBuffer;
    }
}

void BloomPass::init(int width, int height) {
    blurBuffer = new ColorBuffer();
    blurBuffer->init(width, height);
    
    resultBuffer = new ColorBuffer();
    resultBuffer->init(width, height);
    
    // Create mesh and shader to render blur with
    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(UnitQuad::CreateUnitQuad());
    
    // Init shader and model
    blurShader.init();
    unitQuad.init(mesh);
}

void BloomPass::resize(int width, int height) {
    
    //Recreate buffers
    delete blurBuffer;
    blurBuffer = new ColorBuffer();
    blurBuffer->init(width, height);
    
    delete resultBuffer;
    resultBuffer = new ColorBuffer();
    resultBuffer->init(width, height);
}

void BloomPass::horizontalBlur() {
    glm::mat4 matrix(1.0f);
    
    // Draw horizontal blur into the blur buffer
    blurBuffer->bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glDepthMask(GL_FALSE);
    
    blurShader.use();
    
    blurShader.direction = BloomShader::HORIZONTAL;
    blurShader.setUniforms(matrix, matrix, matrix);
    
    unitQuad.render();
    glDepthMask(GL_TRUE);
    
    blurBuffer->unbind();
}

void BloomPass::verticalBlur() {
    glm::mat4 matrix(1.0f);
    
    // Render image to buffer with vertical blur to screen
    resultBuffer->bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glDepthMask(GL_FALSE);
    
    blurBuffer->bindAttachments();
    blurShader.use();
    blurShader.direction = BloomShader::VERTICAL;
    blurShader.setUniforms(matrix, matrix, matrix);
    
    unitQuad.render();
    
    glDepthMask(GL_TRUE);
    
    blurBuffer->unbindAttachments();
    resultBuffer->unbind();
}

void BloomPass::render(glm::mat4 proj, glm::mat4 view, FrameBuffer* bufferToBlur) {
    // Bind buffer textures to blur
    bufferToBlur->bindAttachments();
    
    // Blur texture
    horizontalBlur();
    
    bufferToBlur->unbindAttachments();
    
    verticalBlur();
}

FrameBuffer* BloomPass::getBuffer() {
    return resultBuffer;
}

void BloomPass::bindBufferTextures() {
    this->resultBuffer->bindAttachments();
}

void BloomPass::unbindBufferTextures() {
    this->resultBuffer->unbindAttachments();
}

