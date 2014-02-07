//
//  Shader.cpp
//  ModelViewer
//
//  Created by Mattias Bergström on 2014-01-30.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include "Shader.h"
#include "glm/gtc/matrix_inverse.hpp"
#include <GLFW/glfw3.h>
#include <math.h>
#include "Constants.h"
#include "Mesh.h"
#include <iostream>

Shader::Shader() {
    // Setup default values
    this->programId = 0;
    this->materialBuffer = GL_INVALID_VALUE;
}

Shader::~Shader() {
    glDeleteProgram(programId);
}

void Shader::use() {
    if(programId == 0) {
        throw "Shader not initialized, run init before calling use";
    }
    glUseProgram(this->programId);
}

void Shader::setUniforms(glm::mat4& proj, glm::mat4& view, glm::mat4& model) {
    GLint projId = glGetUniformLocation(this->programId, "proj");
    GLint viewId = glGetUniformLocation(this->programId, "view");
    GLint modelId = glGetUniformLocation(this->programId, "model");
    GLint mvpId = glGetUniformLocation(this->programId, "mvp");
    GLint normalMatrixId = glGetUniformLocation(this->programId, "normal_matrix");
    GLint inverseProjId = glGetUniformLocation(this->programId, "inverse_proj");
    GLint inverseViewId = glGetUniformLocation(this->programId, "inverse_view");
    GLint nearZId = glGetUniformLocation(this->programId, "nearZ");
    GLint farZId = glGetUniformLocation(this->programId, "farZ");
    
    
    glm::mat3 normalMatrix = glm::inverseTranspose(glm::mat3(view * model));
    glm::mat4 inverseProj = glm::inverse(proj);
    glm::mat4 inverseView = glm::inverse(view);
    
    glUniformMatrix4fv(projId, 1, GL_FALSE, glm::value_ptr(proj));
    glUniformMatrix4fv(viewId, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(modelId, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(mvpId, 1, GL_FALSE, glm::value_ptr(proj * view * model));
    glUniformMatrix3fv(normalMatrixId, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    glUniformMatrix4fv(inverseProjId, 1, GL_FALSE, glm::value_ptr(inverseProj));
    glUniformMatrix4fv(inverseViewId, 1, GL_FALSE, glm::value_ptr(inverseView));
    glUniform1f(nearZId, 0.1f);
    glUniform1f(farZId, 100.0f);
    
    glBindBufferBase(GL_UNIFORM_BUFFER, Shader::MATERIAL, materialBuffer);
    glBindBufferBase(GL_UNIFORM_BUFFER, Shader::LIGHT, lightBuffer);
}

void Shader::setupBufferBindings() {
    GLuint bindingPoint = Shader::MATERIAL;
    GLuint blockIndex;
    
    blockIndex = glGetUniformBlockIndex(programId, "Material");
    if(blockIndex != GL_INVALID_INDEX) {
        glUniformBlockBinding(programId, blockIndex, bindingPoint);
        
        glGenBuffers(1, &materialBuffer);
        glBindBuffer(GL_UNIFORM_BUFFER, materialBuffer);
        glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, materialBuffer);
    }
    
    bindingPoint = Shader::LIGHT;
    
    blockIndex = glGetUniformBlockIndex(programId, "Light");
    if(blockIndex != GL_INVALID_INDEX) {
        glUniformBlockBinding(programId, blockIndex, bindingPoint);
        
        glGenBuffers(1, &lightBuffer);
        glBindBuffer(GL_UNIFORM_BUFFER, lightBuffer);
        glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, lightBuffer);
    }
    
}