//
//  Material.h
//  ModelViewer
//
//  Created by Mattias Bergström on 2014-01-31.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef ModelViewer_Material_h
#define ModelViewer_Material_h

#include "glm/glm.hpp"

struct Material {
    glm::vec4 diffuse;
    glm::vec4 ambient;
    glm::vec4 specular;
    float shininess;
};

#endif
