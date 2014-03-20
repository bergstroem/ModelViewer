//
//  DeferredPhongShader.cpp
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-02-02.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include <iostream>
#include "DeferredPhongShader.h"
#include "ShaderLoader.h"
#include "Constants.h"

void DeferredPhongShader::init() {
    ShaderLoader& loader = ShaderLoader::getInstance();
    
    this->programId = loader.loadShaderProgram("passthrough.vs", "deferred_phong.fs");
    
    this->setupBufferBindings();
}

void DeferredPhongShader::setUniforms(glm::mat4 proj, glm::mat4 view, glm::mat4 model) {
    Shader::setUniforms(proj, view, model);
    
    GLint normalSamplerId = glGetUniformLocation(this->programId, "normal_sampler");
    GLint diffuseSamplerId = glGetUniformLocation(this->programId, "diffuse_sampler");
    GLint ambientSamplerId = glGetUniformLocation(this->programId, "ambient_sampler");
    GLint specularSamplerId = glGetUniformLocation(this->programId, "specular_sampler");
    GLint shininessSamplerId = glGetUniformLocation(this->programId, "shininess_sampler");
    GLint depthSamplerId = glGetUniformLocation(this->programId, "depth_sampler");
    GLint shadowSamplerId = glGetUniformLocation(this->programId, "shadow_sampler");
    
    
    glUniform1i(normalSamplerId, TEXTURE_NORMAL_INDEX);
    glUniform1i(depthSamplerId, TEXTURE_DEPTH_INDEX);
    
    // Shadow(s)
    glUniform1i(shadowSamplerId, TEXTURE_SHADOW0_INDEX);
    
    // Materials
    glUniform1i(diffuseSamplerId, TEXTURE_DIFFUSE_INDEX);
    glUniform1i(ambientSamplerId, TEXTURE_AMBIENT_INDEX);
    glUniform1i(specularSamplerId, TEXTURE_SPECULAR_INDEX);
    glUniform1i(shininessSamplerId, TEXTURE_SHININESS_INDEX);
    
}

void DeferredPhongShader::setLightMvp(glm::mat4 mvp) {
    GLuint lightMvpId = glGetUniformLocation(this->programId, "light_mvp");
    
    glUniformMatrix4fv(lightMvpId, 1, GL_FALSE, glm::value_ptr(mvp));
}

void DeferredPhongShader::setLight(LightProperties light) {
    glBindBuffer(GL_UNIFORM_BUFFER, lightBuffer);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(LightProperties), &light, GL_DYNAMIC_DRAW);
}

