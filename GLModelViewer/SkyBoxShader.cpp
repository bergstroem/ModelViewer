//
//  SkyBoxShader.cpp
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-03-07.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include "SkyBoxShader.h"
#include "ShaderLoader.h"
#include "Constants.h"

void SkyBoxShader::init() {
    ShaderLoader& loader = ShaderLoader::getInstance();
    
    this->programId = loader.loadShaderProgram("skybox.vs", "skybox.fs");
    
    this->setupBufferBindings();
}

void SkyBoxShader::setUniforms(glm::mat4& proj, glm::mat4& view, glm::mat4& model) {
    Shader::setUniforms(proj, view, model);
    
    // Add cubemap sampler
    GLint cubeMapId = glGetUniformLocation(this->programId, "cube_map");
    glUniform1i(cubeMapId, TEXTURE_CUBEMAP_INDEX);
}