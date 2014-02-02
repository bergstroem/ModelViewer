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
    
    this->setupBufferBindings();
}

void PhongShader::setUniforms(glm::mat4& proj, glm::mat4& view, glm::mat4& model) {
    Shader::setUniforms(proj, view, model);
    
    // Move to base class?
    glBindBufferBase(GL_UNIFORM_BUFFER, Shader::MATERIAL, materialBuffer);
}

void PhongShader::setMaterial(Material material) {
    //TODO: update material
    glBindBuffer(GL_UNIFORM_BUFFER, materialBuffer);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(Material), &material, GL_DYNAMIC_DRAW);
}