//
//  PassthroughShader.cpp
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-02-03.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//
#include "PassthroughShader.h"
#include "ShaderLoader.h"
#include "Constants.h"

void PassthroughShader::init() {
    ShaderLoader& loader = ShaderLoader::getInstance();
    
    this->programId = loader.loadShaderProgram("passthrough.vs", "passthrough.fs");
    
    this->setupBufferBindings();
}

void PassthroughShader::setUniforms(glm::mat4& proj, glm::mat4& view, glm::mat4& model) {
    Shader::setUniforms(proj, view, model);
    
    GLint colorSamplerId = glGetUniformLocation(this->programId, "color_sampler");
    
    glUniform1i(colorSamplerId, TEXTURE_COLOR_INDEX);

}