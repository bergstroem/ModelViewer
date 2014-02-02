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

class DeferredPhongShader : public Shader {
public:
    void init();
    void setUniforms(glm::mat4& proj, glm::mat4& view, glm::mat4& model);
};

#endif
