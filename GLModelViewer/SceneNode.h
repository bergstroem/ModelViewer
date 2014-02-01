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
    
public:
    // Members
    glm::vec3 position;
    glm::mat4 rotation;
    glm::mat4 modelMatrix;
    
    std::shared_ptr<Mesh> mesh;
    
    // Ctors
    SceneNode();
    ~SceneNode();
    
    // Methods
    virtual void init(std::shared_ptr<Mesh> mesh);
    virtual void render();
};

#endif
