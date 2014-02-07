//
//  DeferredPhongShader.h
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-02-02.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef GLModelViewer_DeferredPhongShader_h
#define GLModelViewer_DeferredPhongShader_h

#include "Shader.h"
#include "LightProperties.h"
#include "glm/gtc/type_ptr.hpp"

class DeferredPhongShader : public Shader {
public:
    void init();
    void setUniforms(glm::mat4& proj, glm::mat4& view, glm::mat4& model);
    void setLightMvp(glm::mat4 mvp);
    void setLight(LightProperties light);
};

#endif
