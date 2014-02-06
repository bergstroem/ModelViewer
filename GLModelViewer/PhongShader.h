//
//  SimpleShader.h
//  ModelViewer
//
//  Created by Mattias Bergström on 2014-01-28.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef ModelViewer_PhongShader_h
#define ModelViewer_PhongShader_h


#include "glm/gtc/type_ptr.hpp"
#include "Shader.h"
#include "Material.h"
#include "LightProperties.h"


class PhongShader : public Shader {
public:
    void setLightMvp(glm::mat4 mvp);
    void setMaterial(Material material);
    void setLight(LightProperties light);
    void init();
};

#endif
