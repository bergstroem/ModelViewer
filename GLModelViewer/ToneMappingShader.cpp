//
//  ToneMappingShader.cpp
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-02-09.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include "ToneMappingShader.h"
#include "ShaderLoader.h"
#include "Constants.h"

void ToneMappingShader::init() {
    ShaderLoader& loader = ShaderLoader::getInstance();
    
    this->programId = loader.loadShaderProgram("passthrough.vs", "tone_mapping.fs");
    
    this->setupBufferBindings();
}

void ToneMappingShader::setUniforms(glm::mat4& proj, glm::mat4& view, glm::mat4& model) {
    Shader::setUniforms(proj, view, model);
    
    GLint colorSamplerId = glGetUniformLocation(this->programId, "color_sampler");
    
    glUniform1i(colorSamplerId, TEXTURE_COLOR_INDEX);
}