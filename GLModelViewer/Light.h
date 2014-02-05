//
//  Light.h
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-02-04.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef GLModelViewer_Light_h
#define GLModelViewer_Light_h

struct Light {
    glm::vec4 position;
    glm::vec4 intensity;
    struct {
        float constant;
        float linear;
        float exponential;
    } Attenuation;
};

#endif
