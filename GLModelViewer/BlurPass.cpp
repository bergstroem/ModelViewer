//
//  BlurPass.cpp
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-01-31.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include "BlurPass.h"
#include "UnitQuad.h"
#include "BlurShader.h"


BlurPass::~BlurPass() {
    if(blurBuffer) {
        delete blurBuffer;
    }
    if(resultBuffer) {
        delete resultBuffer;
    }
}

void BlurPass::init(int width, int height) {
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

void BlurPass::resize(int width, int height) {
    
    //Recreate buffers
    delete blurBuffer;
    blurBuffer = new ColorBuffer();
    blurBuffer->init(width, height);
    
    delete resultBuffer;
    resultBuffer = new ColorBuffer();
    resultBuffer->init(width, height);
}

void BlurPass::horizontalBlur() {
    glm::mat4 matrix(1.0f);
    
    // Draw horizontal blur into the blur buffer
    blurBuffer->bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glDepthMask(GL_FALSE);

    blurShader.use();
    
    blurShader.direction = BlurShader::HORIZONTAL;
    blurShader.setUniforms(matrix, matrix, matrix);
    
    unitQuad.render();
    glDepthMask(GL_TRUE);

    blurBuffer->unbind();
}

void BlurPass::verticalBlur() {
    glm::mat4 matrix(1.0f);
    
    // Render image to buffer with vertical blur to screen
    resultBuffer->bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glDepthMask(GL_FALSE);

    blurBuffer->bindAttachments();
    blurShader.use();
    blurShader.direction = BlurShader::VERTICAL;
    blurShader.setUniforms(matrix, matrix, matrix);
    
    unitQuad.render();
    
    glDepthMask(GL_TRUE);

    blurBuffer->unbindAttachments();
    resultBuffer->unbind();
}

void BlurPass::render(glm::mat4 proj, glm::mat4 view, FrameBuffer* bufferToBlur) {
        // Bind buffer textures to blur
    bufferToBlur->bindAttachments();
    
    // Blur texture
    horizontalBlur();
    
    bufferToBlur->unbindAttachments();
    
    verticalBlur();
}

FrameBuffer* BlurPass::getBuffer() {
    return resultBuffer;
}

void BlurPass::bindBufferTextures() {
    this->resultBuffer->bindAttachments();
}

void BlurPass::unbindBufferTextures() {
    this->resultBuffer->unbindAttachments();
}

