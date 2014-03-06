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
#include "glm/gtc/matrix_transform.hpp"
#include "BezierCurve.h"

class CameraMovement {
    float rotationYaw;
    float rotationPitch;
    float lastTime;
    float deltaTime;
    float turningAmount;
    
    bool hasRegisteredTurnKey;
    bool shouldCalculateCurve;
    
    glm::vec3 movementDirection;
    
    BezierCurve curve;
    float currentCurveT;
    glm::vec3 lastPosition;
    
    GLFWwindow* window;
    
public:
    glm::vec3 position;
    
    glm::vec3 lookatDirection;
    float velocity;
    bool isSmoothMovement;
    
    CameraMovement(GLFWwindow* window);
    
    void update();
    void updateSmoothMovement();
    void updateFPSMovement();
    
    
};

#endif /* defined(__GLModelViewer__CameraMovement__) */
