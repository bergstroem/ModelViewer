//
//  Shader.h
//  ModelViewer
//
//  Created by Mattias Bergström on 2014-01-28.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef ModelViewer_Shader_h
#define ModelViewer_Shader_h

#include <GL/glew.h>
#include "glm/gtc/type_ptr.hpp"

/*
 * Abstract class, represents a shader program
 */
class Shader {
protected:
    unsigned int materialBuffer;
    unsigned int lightBuffer;
    
    // Will be called after setup attributes is done and has linked the program
    void setupBufferBindings();
    int createUniformBuffer();
public:
    enum UniformBufferBindingPoints {
        MATERIAL,
        LIGHT// TODO: More binding points
    };
    
    unsigned int programId;
    
    Shader();
    ~Shader();
  
    virtual void init() = 0;
    void use();
    virtual void setUniforms(glm::mat4& proj, glm::mat4& view, glm::mat4& model);
    
};

#endif
