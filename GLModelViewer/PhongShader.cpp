//
//  SimpleShader.cpp
//  ModelViewer
//
//  Created by Mattias Bergström on 2014-01-28.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include <iostream>
#include "Mesh.h"
#include "PhongShader.h"
#include "ShaderLoader.h"
#include "glm/gtc/matrix_inverse.hpp"

void PhongShader::init() {
    ShaderLoader& loader = ShaderLoader::getInstance();
    
    this->programId = loader.loadShaderProgram("/Users/mattiasbergstrom/Documents/src/GLModelViewer/GLModelViewer/phong_shader.vs", "/Users/mattiasbergstrom/Documents/src/GLModelViewer/GLModelViewer/phong_shader.fs");
    
    setupBufferBindings();
}

void PhongShader::setUniforms(glm::mat4& proj, glm::mat4& view, glm::mat4& model) {
    Shader::setUniforms(proj, view, model);
    
    GLint shadowSamplerId = glGetUniformLocation(this->programId, "shadow_sampler");
    
    glUniform1i(shadowSamplerId, TEXTURE_DEPTH_INDEX);
}

void PhongShader::setLightMvp(glm::mat4 mvp) {
    GLuint lightMvpId = glGetUniformLocation(this->programId, "light_mvp");
    
    glUniformMatrix4fv(lightMvpId, 1, GL_FALSE, glm::value_ptr(mvp));
}

void PhongShader::setMaterial(Material material) {
    glBindBuffer(GL_UNIFORM_BUFFER, materialBuffer);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(Material), &material, GL_DYNAMIC_DRAW);
}

void PhongShader::setLight(LightProperties light) {
    glBindBuffer(GL_UNIFORM_BUFFER, lightBuffer);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(LightProperties), &light, GL_DYNAMIC_DRAW);
}