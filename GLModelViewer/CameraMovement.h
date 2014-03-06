//
//  CameraMovement.h
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-03-06.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef __GLModelViewer__CameraMovement__
#define __GLModelViewer__CameraMovement__

#include <iostream>
#include <GLFW/glfw3.h>
#include "glm/gtc/type_ptr.hpp"

class CameraMovement {
    float acceleration;
    float rotationYaw;
    float rotationPitch;
    float lastTime;
    
    bool isSmoothMovement;
    
    GLFWwindow* window;
    
public:
    glm::vec3 movementDirection;
    glm::vec3 lookatDirection;
    float velocity;
    
    CameraMovement(GLFWwindow* window);
    
    void update();
    void updateSmoothMovement();
    void updateFPSMovement();
    
};

#endif /* defined(__GLModelViewer__CameraMovement__) */
