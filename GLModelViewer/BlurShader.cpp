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
    
    this->programId = loader.loadShaderProgram("/Users/mattiasbergstrom/Documents/src/GLModelViewer/GLModelViewer/passthrough.vs", "/Users/mattiasbergstrom/Documents/src/GLModelViewer/GLModelViewer/blur_shader.fs");
}

void BlurShader::setUniforms(glm::mat4& proj, glm::mat4& view, glm::mat4& model) {
    Shader::setUniforms(proj, view, model);
    
    glm::mat3 normalMatrix = glm::inverseTranspose(glm::mat3(view * model));
    GLint normalMatrixId = glGetUniformLocation(this->programId, "normal_matrix");
    GLint textureSamplerId = glGetUniformLocation(this->programId, "texture_sampler");
    GLint depthSamplerId = glGetUniformLocation(this->programId, "depth_sampler");
    GLint directionId = glGetUniformLocation(this->programId, "direction");
    
    glUniformMatrix3fv(normalMatrixId, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    glUniform1i(textureSamplerId, 0);
    glUniform1i(depthSamplerId, 1);
    glUniform1i(directionId, direction);
}