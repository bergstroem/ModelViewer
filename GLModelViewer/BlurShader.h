//
//  BlurShader.h
//  ModelViewer
//
//  Created by Mattias Bergström on 2014-01-30.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef ModelViewer_BlurShader_h
#define ModelViewer_BlurShader_h

#include "glm/gtc/type_ptr.hpp"
#include "Shader.h"


class BlurShader : public Shader {
public:
    enum BlurDirection {
        HORIZONTAL = 0,
        VERTICAL = 1
    };
    BlurDirection direction;
    
    void init();
    void setUniforms(glm::mat4& proj, glm::mat4& view, glm::mat4& model);
};

#endif
