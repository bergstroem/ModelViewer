//
//  SimpleModel.cpp
//  ModelViewer
//
//  Created by Mattias Bergström on 2014-01-30.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include "SimpleModel.h"
#include <GLFW/glfw3.h>

void SimpleModel::render() {
    //Rotate the model around its y-axis
    glm::vec3 v_rotation = glm::vec3(0.0f, 1.0f, 0.0f);
    modelMatrix = glm::translate(glm::mat4(1.0f), position);
    //rotation = glm::rotate(glm::mat4(1.0f), 50.0f * (float)glfwGetTime(), v_rotation);
    
    SceneNode::render();
}
