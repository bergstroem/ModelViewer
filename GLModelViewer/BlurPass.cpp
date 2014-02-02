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
    if(pass1Buffer) {
        delete pass1Buffer;
    }
    if(pass2Buffer) {
        delete pass2Buffer;
    }
}

void BlurPass::init(int width, int height) {
    pass1Buffer = new FrameBuffer();
    pass2Buffer = new FrameBuffer();
    pass1Buffer->init(width, height);
    pass2Buffer->init(width, height);
    
    // Create mesh and shader to render blur with
    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(UnitQuad::CreateUnitQuad());
    
    // Init shader and model
    blurShader.init();
    unitQuad.init(mesh);
    
    shader.init();
}

void BlurPass::resize(int width, int height) {
    //Recreate buffers
    delete pass1Buffer;
    delete pass2Buffer;
    pass1Buffer = new FrameBuffer();
    pass2Buffer = new FrameBuffer();
    
    pass1Buffer->init(width, height);
    pass2Buffer->init(width, height);
}

void BlurPass::horizontalBlur() {
    glm::mat4 matrix(1.0f);
    // Draw horizontal blur into the vertical blur buffer
    pass2Buffer->bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Bind texture from horizontal buffer to sample from it
    pass1Buffer->bindTextures();
    
    blurShader.use();
    
    blurShader.setUniforms(matrix, matrix, matrix);
    blurShader.direction = BlurShader::HORIZONTAL;
    
    unitQuad.render();
    
    pass1Buffer->unbindTextures();
    pass2Buffer->unbind();
}

void BlurPass::verticalBlur() {
    glm::mat4 matrix(1.0f);
    // Render image with vertical blur to screen
    pass2Buffer->bindTextures();
    
    blurShader.use();
    
    blurShader.setUniforms(matrix, matrix, matrix);
    blurShader.direction = BlurShader::VERTICAL;
    
    unitQuad.render();
    pass2Buffer->unbindTextures();
}

void BlurPass::render(glm::mat4 proj, glm::mat4 view, std::vector<std::shared_ptr<SceneNode>> nodes) {
    
    // Draw image to buffer
    pass1Buffer->bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        (*it)->render();
    }
    
    pass1Buffer->unbind();
    
    horizontalBlur();
    verticalBlur();
}

