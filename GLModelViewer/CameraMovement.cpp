//
//  CameraMovement.cpp
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-03-06.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include "CameraMovement.h"
#include "MathHelper.h"

CameraMovement::CameraMovement(GLFWwindow* window) {
    this->velocity = 0.0f;
    this->acceleration = 0.0f;
    this->rotationYaw = 0.0f;
    this->rotationPitch = 0.0f;
    this->lastTime = 0.0f;
    this->isSmoothMovement = false;
    this->window = window;
}


void CameraMovement::update() {
    if(this->isSmoothMovement) {
        updateSmoothMovement();
    } else {
        updateFPSMovement();
    }
}

void CameraMovement::updateSmoothMovement() {
    
}

void CameraMovement::updateFPSMovement() {
    double currentTime = glfwGetTime();
    
    float deltaTime = float(currentTime - lastTime);
    
    glm::vec3 movement;
    
    /* Translation input */
    
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        movement.z -= cosf(rotationYaw);
        movement.x += sinf(rotationYaw);
        
    } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        movement.z += cosf(rotationYaw);
        movement.x -= sinf(rotationYaw);
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        movement.z -= sinf(rotationYaw);
        movement.x -= cosf(rotationYaw);
    } else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        movement.z += sinf(rotationYaw);
        movement.x += cosf(rotationYaw);
    }
    
    /* Rotation input */
    
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        rotationYaw -= 2.0f * deltaTime;
    } else if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        rotationYaw += 2.0f * deltaTime;
    }
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        rotationPitch += 2.0f * deltaTime;
    } else if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        rotationPitch -= 2.0 * deltaTime;
    }
    
    // Clamp rotationPitch to avoid gimbal lock
    rotationPitch = CLAMP<float>(rotationPitch, -M_PI/2 + 0.02, +M_PI/2 - 0.02);
    
    
    if(glm::length(movement) > 0) {
        movementDirection = glm::normalize(movement) * deltaTime;
        
        velocity = glm::length(movement) * 4.0f;
    } else {
        velocity = 0.95f * velocity;
    }
    
    lookatDirection = glm::vec3(1.0f * cosf(rotationPitch) * sinf(rotationYaw),
                                    1.0f * sinf(rotationPitch),
                                    -1.0f * cosf(rotationPitch) * cosf(rotationYaw));
    
    lastTime = currentTime;
}
