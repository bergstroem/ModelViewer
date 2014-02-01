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
    GLint normalMatrixId = glGetUniformLocation(this->programId, "normal_matrix");
    GLint nearZId = glGetUniformLocation(this->programId, "nearZ");
    GLint farZId = glGetUniformLocation(this->programId, "farZ");
    
    glm::mat3 normalMatrix = glm::inverseTranspose(glm::mat3(view * model));
    
    glUniformMatrix4fv(projId, 1, GL_FALSE, glm::value_ptr(proj));
    glUniformMatrix4fv(viewId, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(modelId, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix3fv(normalMatrixId, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    glUniform1f(nearZId, 0.1f);
    glUniform1f(farZId, 1000.0f);
}

void Shader::setupAttributes() {
    
    // Bind attrib locations
    glBindAttribLocation(programId, SHADER_POSITION_LOCATION, "position");
    glBindAttribLocation(programId, SHADER_NORMAL_LOCATION, "normal");
    glBindAttribLocation(programId, SHADER_COLOR_LOCATION, "color");
    
    // Bind frag locations
    glBindFragDataLocation(programId, DIFFUSE_TEXTURE_INDEX, "outColor");
    glBindFragDataLocation(programId, NORMAL_TEXTURE_INDEX, "outNormal");
    glBindFragDataLocation(programId, DEPTH_TEXTURE_INDEX, "outDepth");
    glBindFragDataLocation(programId, POSITION_TEXTURE_INDEX, "outPosition");
    glBindFragDataLocation(programId, AMBIENT_TEXTURE_INDEX, "outAmbient");
    glBindFragDataLocation(programId, SPECULAR_TEXTURE_INDEX, "outSpecular");
    glBindFragDataLocation(programId, SHININESS_TEXTURE_INDEX, "outShininess");
    
    // Link everything!
    glLinkProgram(programId);
    
    // Must be performed on a linked program
    this->setupBufferBindings();
}

void Shader::setupBufferBindings() {
    // No buffers in base class, override in subclass if buffer bindings are needed
    GLuint bindingPoint = Shader::MATERIAL;
    GLuint blockIndex;
    
    blockIndex = glGetUniformBlockIndex(programId, "Material");
    if(blockIndex != GL_INVALID_INDEX) {
        glUniformBlockBinding(programId, blockIndex, bindingPoint);
        
        glGenBuffers(1, &materialBuffer);
        glBindBuffer(GL_UNIFORM_BUFFER, materialBuffer);
        glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, materialBuffer);
    }
}
