//
//  GeometryShader.cpp
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-02-01.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include "GeometryShader.h"
#include "ShaderLoader.h"

void GeometryShader::init() {
    ShaderLoader& loader = ShaderLoader::getInstance();
    
    this->programId = loader.loadShaderProgram("/Users/mattiasbergstrom/Documents/src/GLModelViewer/GLModelViewer/geometry.vs", "/Users/mattiasbergstrom/Documents/src/GLModelViewer/GLModelViewer/geometry.fs");
}

void GeometryShader::setMaterial(Material material) {
    //TODO: update material
    glBindBuffer(GL_UNIFORM_BUFFER, materialBuffer);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(Material), &material, GL_DYNAMIC_DRAW);
}

void GeometryShader::setUniforms(glm::mat4& proj, glm::mat4& view, glm::mat4& model) {
    Shader::setUniforms(proj, view, model);
    
    // Move to base class?
    glBindBufferBase(GL_UNIFORM_BUFFER, Shader::MATERIAL, materialBuffer);
}
