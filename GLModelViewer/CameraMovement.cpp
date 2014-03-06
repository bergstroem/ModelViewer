//
//  CameraMovement.cpp
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-03-06.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include "CameraMovement.h"
#include "MathHelper.h"
#include <cmath>
#include <iostream>

#define ACCELERATION_CONSTANT 0.8;

CameraMovement::CameraMovement(GLFWwindow* window) {
    this->velocity = 0.0f;
    this->rotationYaw = 0.0f;
    this->rotationPitch = 0.0f;
    this->lastTime = 0.0f;
    this->turningAmount = 0.0f;
    this->currentCurveT = 0.0f;
    this->isSmoothMovement = false;
    this->shouldCalculateCurve = false;
    this->hasRegisteredTurnKey = false;
    this->window = window;
    
    this->lookatDirection = glm::vec3(0.0f, 0.0f, -1.0f);
    
    this->curve.startPoint = glm::vec3(0.0f, 0.0f, 0.0f);
    this->curve.controlPoint = this->curve.startPoint + glm::normalize(lookatDirection) * 3.f;
    this->curve.endPoint = this->curve.startPoint + glm::normalize(lookatDirection) * 6.f;
}


void CameraMovement::update() {
    double currentTime = glfwGetTime();
    
    deltaTime = float(currentTime - lastTime);
    
    if(this->isSmoothMovement) {
        updateSmoothMovement();
    } else {
        updateFPSMovement();
    }
    lastTime = currentTime;
}

void CameraMovement::updateSmoothMovement() {
    
    /* Acceleration/Decceleration */
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        velocity += deltaTime * ACCELERATION_CONSTANT;
        velocity = CLAMP<float>(velocity, 0, 0.6);
    } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        velocity *= 0.9f;
    } else {
        velocity *= 0.95f;
    }
    
    if(std::abs(velocity) < 0.001f) {
        velocity = 0.0f;
    }
    
    this->currentCurveT += this->deltaTime  * this->velocity;
    
    /* Turning */
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && !hasRegisteredTurnKey) {
        turningAmount = 1.f;
        hasRegisteredTurnKey = true;
        shouldCalculateCurve = true;
    } else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && !hasRegisteredTurnKey) {
        turningAmount = -1.f;
        hasRegisteredTurnKey = true;
        shouldCalculateCurve = true;
    } else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE) {
        turningAmount = 0.0f;
        hasRegisteredTurnKey = false;
    }
    
    glm::vec3 deltaMovement;
    
    // If within the curve, get new position
    if(this->currentCurveT <= 1.0f) {
        this->position = glm::vec3(curve.getPosition(currentCurveT));
        deltaMovement = position - lastPosition;
    }
    else { // Otherwise create new curve and start from beginning
        this->curve.startPoint = this->curve.getPosition(currentCurveT);
        this->curve.controlPoint = this->curve.startPoint + glm::normalize(lookatDirection) * 3.f;
        this->curve.endPoint = this->curve.startPoint + glm::normalize(lookatDirection) * 6.f;
        currentCurveT = 0.0f;
    }
    
    // Update lookatDirection to match travel direction
    if(glm::length(deltaMovement) > 0.0f) {
        this->lookatDirection = deltaMovement;
        
        // If turning, create new bezier curve
        if(std::abs(turningAmount) > 0.0f && shouldCalculateCurve) {
            this->curve.startPoint = this->curve.getPosition(currentCurveT);
            this->curve.controlPoint = this->curve.startPoint + glm::normalize(lookatDirection) * 3.f;
            
            glm::mat4 rotation = glm::rotate(glm::mat4(1.0f),
                                             turningAmount * 60.f,
                                             glm::vec3(0.0f,1.0f, 0.0f));
            
            glm::vec3 rotatedPoint = glm::vec3(rotation * glm::vec4(glm::normalize(lookatDirection), 1.0));
            
            this->curve.endPoint = this->curve.startPoint + rotatedPoint * 6.f;
            
            shouldCalculateCurve = false;
            currentCurveT = 0.0f;
        }
    }
    
    this->lastPosition = this->position;
}

void CameraMovement::updateFPSMovement() {
    
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
        velocity *= 0.95f;
    }
    
    this->position += movementDirection * velocity;
    
    lookatDirection = glm::vec3(1.0f * cosf(rotationPitch) * sinf(rotationYaw),
                                    1.0f * sinf(rotationPitch),
                                    -1.0f * cosf(rotationPitch) * cosf(rotationYaw));
    
    
}
