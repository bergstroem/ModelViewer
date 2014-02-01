//
//  Model.h
//  ModelViewer
//
//  Created by Mattias Bergström on 2014-01-28.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef ModelViewer_SceneNode_h
#define ModelViewer_SceneNode_h

#include <memory>
#include "Mesh.h"
#include "PhongShader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

/*
 * Base class for all scene nodes.
 */
class SceneNode {
protected:
    // Members
    std::shared_ptr<Shader> shaderProgram;
    std::shared_ptr<Mesh> mesh;
    glm::mat4 modelMatrix;
    unsigned int vao;
    
    // Methods
    void bindVAO();
    void unbindVAO();
    
public:
    // Members
    glm::vec3 position;
    glm::mat4 rotation;
    
    // Ctors
    SceneNode();
    ~SceneNode();
    
    // Methods
    virtual void init(std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shaderProgram);
    virtual void render(glm::mat4 proj, glm::mat4 view);
};

#endif
