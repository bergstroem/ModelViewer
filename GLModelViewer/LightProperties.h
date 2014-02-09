//
//  Light.h
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-02-04.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef GLModelViewer_Light_h
#define GLModelViewer_Light_h

#include <glm/glm.hpp>

/*
 * Point light
 */
struct LightProperties {
    glm::vec4 position;
    glm::vec4 intensity;
    glm::vec4 direction;
    float angle;
    float spotExponent;
    float constantAtt;
    float linearAtt;
    float exponentialAtt;
};

class LightFactory {
public:
    static LightProperties Dark(glm::vec3 color) {
        LightProperties light;
        light.intensity = glm::vec4(color, 1.0);
        light.position = glm::vec4(0.0, 0.0, 0.0, 1.0);
        light.exponentialAtt = 0.1f;
        light.linearAtt = 0.2f;
        light.constantAtt = 1.0f;
        light.direction = glm::vec4(0.0, -1.0, 0.0, 0.0);
        light.angle = 30.0f;
        light.spotExponent = 2;
        return light;
    }
    static LightProperties Medium(glm::vec3 color) {
        LightProperties light;
        light.intensity = glm::vec4(color, 1.0);
        light.position = glm::vec4(0.0, 0.0, 0.0, 1.0);
        light.exponentialAtt = 0.02f;
        light.linearAtt = 0.2f;
        light.constantAtt = 1.0f;
        light.direction = glm::vec4(0.0, -1.0, 0.0, 0.0);
        light.angle = 30.0f;
        light.spotExponent = 4;
        return light;
    }
    static LightProperties Bright(glm::vec3 color) {
        LightProperties light;
        light.intensity = glm::vec4(color, 0.1);
        light.position = glm::vec4(0.0, 0.0, 0.0, 1.0);
        light.exponentialAtt = 0.001f;
        light.linearAtt = 0.001f;
        light.constantAtt = 1.0f;
        light.direction = glm::vec4(0.0, -1.0, 0.0, 0.0);
        light.angle = 45.0f;
        light.spotExponent = 4;
        return light;
    }
};

#endif
