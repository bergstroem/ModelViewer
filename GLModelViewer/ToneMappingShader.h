//
//  ToneMappingShader.h
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-02-09.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef __GLModelViewer__ToneMappingShader__
#define __GLModelViewer__ToneMappingShader__

#include "Shader.h"

class ToneMappingShader : public Shader {
public:
    void init();
    void setUniforms(glm::mat4 proj, glm::mat4 view, glm::mat4 model);
    void setExposure(float exposure);
};


#endif
