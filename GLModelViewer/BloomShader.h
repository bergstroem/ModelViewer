//
//  BloomShader.h
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-03-20.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef __GLModelViewer__BloomShader__
#define __GLModelViewer__BloomShader__

#include "glm/gtc/type_ptr.hpp"
#include "Shader.h"


class BloomShader : public Shader {
public:
    enum BlurDirection {
        HORIZONTAL = 0,
        VERTICAL = 1
    };
    BlurDirection direction;
    
    void init();
    void setUniforms(glm::mat4 proj, glm::mat4 view, glm::mat4 model);
};

#endif /* defined(__GLModelViewer__BloomShader__) */
