//
//  PerspectivePassthroughShader.h
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-02-05.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef __GLModelViewer__PerspectivePassthroughShader__
#define __GLModelViewer__PerspectivePassthroughShader__

#include "Shader.h"

class PerspectivePassthroughShader : public Shader {
    
public:
    void init();
    void setUniforms(glm::mat4& proj, glm::mat4& view, glm::mat4& model);
};

#endif
