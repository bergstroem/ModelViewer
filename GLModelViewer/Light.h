//
//  Light.h
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-02-04.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef GLModelViewer_Light_h
#define GLModelViewer_Light_h

/*
 * Point light
 */
struct Light {
    glm::vec4 position;
    glm::vec4 intensity;
    glm::vec3 direction;
    float angle;
    float spotExponent;
    float constantAtt;
    float linearAtt;
    float exponentialAtt;
};

class LightFactory {
public:
    static Light Dark(glm::vec3 color) {
        Light light;
        light.intensity = glm::vec4(color, 1.0);
        light.position = glm::vec4(0.0, 0.0, 0.0, 1.0);
        light.exponentialAtt = 0.1f;
        light.linearAtt = 0.2f;
        light.constantAtt = 1.0f;
        light.direction = glm::vec3(0.0, -1.0, 0.0);
        light.angle = 90.0f;
        light.spotExponent = 2;
        return light;
    }
    static Light Medium(glm::vec3 color) {
        Light light;
        light.intensity = glm::vec4(color, 1.0);
        light.position = glm::vec4(0.0, 0.0, 0.0, 1.0);
        light.exponentialAtt = 0.02f;
        light.linearAtt = 0.2f;
        light.constantAtt = 1.0f;
        light.direction = glm::vec3(0.0, -1.0, 0.0);
        light.angle = 90.0f;
        light.spotExponent = 2;
        return light;
    }
    static Light Bright(glm::vec3 color) {
        Light light;
        light.intensity = glm::vec4(color, 1.0);
        light.position = glm::vec4(0.0, 0.0, 0.0, 1.0);
        light.exponentialAtt = 0.01f;
        light.linearAtt = 0.01f;
        light.constantAtt = 1.0f;
        light.direction = glm::vec3(0.0, -1.0, 0.0);
        light.angle = 90.0f;
        light.spotExponent = 6;
        return light;
    }
};

#endif
