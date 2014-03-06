//
//  Camera.h
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-03-05.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef __GLModelViewer__Camera__
#define __GLModelViewer__Camera__

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

enum CameraProjection {
    PROJECTION_OBLIQUE,
    PROJECTION_ORTHOGONAL,
    PROJECTION_PERSPECTIVE
};

class Camera {
    CameraProjection cameraProjection;
    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;
    
    
public:
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;
    
    float fieldOfView;
    float farZ;
    float nearZ;
    float aspectRatio;
    
    Camera();
    
    void init(float aspectRatio, float fieldOfView, float nearZ, float farZ);
    
    void updateProjection();
    void updateView();
    void update();
    
    CameraProjection getCameraProjection();
    void setCameraProjection(CameraProjection cameraProjection);
    
    glm::mat4 getCameraViewTransform();
    glm::mat4 getCameraProjectionTransform();
};

#endif /* defined(__GLModelViewer__Camera__) */
