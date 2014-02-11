//
//  BlurShader.cpp
//  ModelViewer
//
//  Created by Mattias Bergström on 2014-01-30.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include "BlurShader.h"
#include "ShaderLoader.h"
#include "glm/gtc/matrix_inverse.hpp"

void BlurShader::init() {
    this->direction = BlurShader::HORIZONTAL;
    ShaderLoader& loader = ShaderLoader::getInstance();
    
    this->programId = loader.loadShaderProgram("passthrough.vs", "blur_shader.fs");
    
    setupBufferBindings();
}

void BlurShader::setUniforms(glm::mat4& proj, glm::mat4& view, glm::mat4& model) {
    Shader::setUniforms(proj, view, model);
    
    GLint textureSamplerId = glGetUniformLocation(this->programId, "texture_sampler");
    GLint directionId = glGetUniformLocation(this->programId, "direction");
    
    glUniform1i(textureSamplerId, 0);
    glUniform1i(directionId, direction);
}