//
//  Camera.cpp
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-03-05.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//
#include "Camera.h"

Camera::Camera() {
    this->position = glm::vec3(0.0f);
    this->target = glm::vec3(0.0f, 0.0f, -1.0f);
    this->up = glm::vec3(0.0f, 1.0f, 0.0f);
    
    this->fieldOfView = 60.f;
    this->farZ = 1000.f;
    this->nearZ = 0.1f;
    this->aspectRatio = 1.f;
    
    this->cameraProjection = CameraProjection::PROJECTION_PERSPECTIVE;
    
    lookAt(this->position, this->target, this->up);
}

void Camera::init(float aspectRatio, float fieldOfView, float nearZ, float farZ) {
    this->fieldOfView = fieldOfView;
    this->farZ = farZ;
    this->nearZ = nearZ;
    this->aspectRatio = aspectRatio;
}

void Camera::lookAt(glm::vec3 target) {
    this->lookAt(this->position, this->target, this->up);
}

void Camera::lookAt(glm::vec3 position, glm::vec3 target, glm::vec3 up) {
    this->up = up;
    this->position = position;
    this->target = target;
    this->viewMatrix = glm::lookAt(position, target, up);
}

void Camera::updateProjection() {
    switch(this->cameraProjection) {
        case CameraProjection::PROJECTION_PERSPECTIVE:
            this->projectionMatrix = glm::perspective(this->fieldOfView, this->aspectRatio, this->nearZ, this->farZ);
            break;
        case CameraProjection::PROJECTION_ORTHOGONAL:
            this->projectionMatrix = glm::ortho(-4.0f*this->aspectRatio/2, 4.0f*this->aspectRatio/2, -4.0f, 4.f, -100.0f, 100.f);
            break;
        case CameraProjection::PROJECTION_OBLIQUE:
            glm::mat4 ortho = glm::ortho( -4.0f*this->aspectRatio/2, 4.0f*this->aspectRatio/2, -4.0f, 4.f, -100.0f, 100.f );
            
            glm::mat4 skew = glm::mat4(1.0f, 0.0f, -0.5f*cosf(26.565f*M_PI/180.f), 0.0f,
                                       0.0f, 1.0f, -0.5f*sinf(26.565f*M_PI/180.f), 0.0f,
                                       0.0f, 0.0f, 1.0f, 0.0f,
                                       0.0f, 0.0f, 0.0f, 1.0f);
            
            this->projectionMatrix = ortho * glm::transpose(skew);
            
            break;
    }
}

/* Getters and setters */

CameraProjection Camera::getCameraProjection() {
    return this->cameraProjection;
}

void Camera::setCameraProjection(CameraProjection cameraProjection) {
    this->cameraProjection = cameraProjection;
    updateProjection();
}

glm::mat4 Camera::getCameraViewTransform() {
    return this->viewMatrix;
}

glm::mat4 Camera::getCameraProjectionTransform() {
    return this->projectionMatrix;
}

