//
//  ShaderLoader.cpp
//  ModelViewer
//
//  Created by Mattias Bergström on 2014-01-28.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include "ShaderLoader.h"
#include <iostream>
#include <fstream>
#include "Constants.h"
#include "Shader.h"

int ShaderLoader::loadShaderProgram(std::string vertexShader, std::string fragmentShader) {
    
    unsigned int vertexShaderId = this->loadVertexShader(vertexShader);
    unsigned int fragmentShaderId = this->loadFragmentShader(fragmentShader);
    
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShaderId);
    glAttachShader(shaderProgram, fragmentShaderId);
    
    // Bind attrib locations
    glBindAttribLocation(shaderProgram, SHADER_POSITION_LOCATION, "position");
    glBindAttribLocation(shaderProgram, SHADER_NORMAL_LOCATION, "normal");
    glBindAttribLocation(shaderProgram, SHADER_COLOR_LOCATION, "color");
    
    // Bind frag locations
    glBindFragDataLocation(shaderProgram, TEXTURE_DIFFUSE_INDEX, "outDiffuse");
    glBindFragDataLocation(shaderProgram, TEXTURE_NORMAL_INDEX, "outNormal");
    glBindFragDataLocation(shaderProgram, TEXTURE_POSITION_INDEX, "outPosition");
    glBindFragDataLocation(shaderProgram, TEXTURE_AMBIENT_INDEX, "outAmbient");
    glBindFragDataLocation(shaderProgram, TEXTURE_SPECULAR_INDEX, "outSpecular");
    glBindFragDataLocation(shaderProgram, TEXTURE_SHININESS_INDEX, "outShininess");
    
    // Fragment location to screen, always 0
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    
    // Link everything!
    glLinkProgram(shaderProgram);
    
    return shaderProgram;
}

int ShaderLoader::loadVertexShader(std::string vertexShader) {
    
    unsigned int vertexShaderId;
    
    auto it = this->loadedVertexShaders.find(vertexShader);
    if(it != this->loadedVertexShaders.end()) {
        // Shader found, was loaded
        vertexShaderId = it->second;
    } else {
        // Shader not found, load and add to loaded shaders
        vertexShaderId = loadShader(GL_VERTEX_SHADER, vertexShader);
        this->loadedVertexShaders[vertexShader] = vertexShaderId;
    }
    return vertexShaderId;
}

int ShaderLoader::loadFragmentShader(std::string fragmentShader) {
    
    unsigned int fragmentShaderId;
    
    auto it = this->loadedFragmentShaders.find(fragmentShader);
    if(it != this->loadedFragmentShaders.end()) {
        // Shader found, was loaded
        fragmentShaderId = it->second;
    } else {
        // Shader not found, load and add to loaded shaders
        fragmentShaderId = loadShader(GL_FRAGMENT_SHADER, fragmentShader);
        this->loadedFragmentShaders[fragmentShader] = fragmentShaderId;
    }
    return fragmentShaderId;
}

int ShaderLoader::loadShader(GLenum shaderType, std::string shader) {
    
    std::ifstream file(shader);
    
    if(!file.is_open())
        throw "Shader file not found";
    
    std::string contentStr = std::string((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
    
    const char* content = contentStr.c_str();
    
    GLuint shaderId = glCreateShader(shaderType);
    
    glShaderSource(shaderId, 1,  &content, NULL);
    glCompileShader(shaderId);
    
    if(!shaderStatusOK(shaderId)) {
        throw "Shader compile error";
    }
    
    return shaderId;
}


bool ShaderLoader::shaderStatusOK(int shaderId) {
    GLint status;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
    if(status != GL_TRUE) {
        char buffer[512];
        glGetShaderInfoLog(shaderId, 512, NULL, buffer);
        
        std::string err(buffer);
        std::cerr << err << std::endl;
        return false;
    }
    
    return true;
}
