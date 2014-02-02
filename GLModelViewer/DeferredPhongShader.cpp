//
//  DeferredPhongShader.cpp
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-02-02.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include "DeferredPhongShader.h"
#include "ShaderLoader.h"
#include "Constants.h"

void DeferredPhongShader::init() {
    ShaderLoader& loader = ShaderLoader::getInstance();
    
    this->programId = loader.loadShaderProgram("/Users/mattiasbergstrom/Documents/src/GLModelViewer/GLModelViewer/passthrough.vs", "/Users/mattiasbergstrom/Documents/src/GLModelViewer/GLModelViewer/deferred_phong.fs");
    
    this->setupBufferBindings();
}

void DeferredPhongShader::setUniforms(glm::mat4& proj, glm::mat4& view, glm::mat4& model) {
    Shader::setUniforms(proj, view, model);
    
    GLint positionSamplerId = glGetUniformLocation(this->programId, "position_sampler");
    GLint normalSamplerId = glGetUniformLocation(this->programId, "normal_sampler");
    GLint diffuseSamplerId = glGetUniformLocation(this->programId, "diffuse_sampler");
    GLint ambientSamplerId = glGetUniformLocation(this->programId, "ambient_sampler");
    GLint specularSamplerId = glGetUniformLocation(this->programId, "specular_sampler");
    GLint shininessSamplerId = glGetUniformLocation(this->programId, "shininess_sampler");
    
    glUniform1i(positionSamplerId, POSITION_TEXTURE_INDEX);
    glUniform1i(normalSamplerId, NORMAL_TEXTURE_INDEX);
    glUniform1i(diffuseSamplerId, DIFFUSE_TEXTURE_INDEX);
    glUniform1i(ambientSamplerId, AMBIENT_TEXTURE_INDEX);
    glUniform1i(specularSamplerId, SPECULAR_TEXTURE_INDEX);
    glUniform1i(shininessSamplerId, SHININESS_TEXTURE_INDEX);
    
}