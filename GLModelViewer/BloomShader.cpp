//
//  BloomShader.cpp
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-03-20.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include "BloomShader.h"
#include "ShaderLoader.h"
#include "glm/gtc/matrix_inverse.hpp"

void BloomShader::init() {
    this->direction = BlurDirection::HORIZONTAL;
    ShaderLoader& loader = ShaderLoader::getInstance();
    
    this->programId = loader.loadShaderProgram("passthrough.vs", "bloom_shader.fs");
    
    setupBufferBindings();
}

void BloomShader::setUniforms(glm::mat4 proj, glm::mat4 view, glm::mat4 model) {
    Shader::setUniforms(proj, view, model);
    
    GLint textureSamplerId = glGetUniformLocation(this->programId, "texture_sampler");
    GLint directionId = glGetUniformLocation(this->programId, "direction");
    
    glUniform1i(textureSamplerId, 0);
    glUniform1i(directionId, direction);
}