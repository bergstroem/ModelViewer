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

void PhongShader::setMaterial(Material material) {
    glBindBuffer(GL_UNIFORM_BUFFER, materialBuffer);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(Material), &material, GL_DYNAMIC_DRAW);
}

void PhongShader::setLight(Light light) {
    glBindBuffer(GL_UNIFORM_BUFFER, lightBuffer);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(Light), &light, GL_DYNAMIC_DRAW);
}