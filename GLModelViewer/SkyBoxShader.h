//
//  SkyBoxShader.h
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-03-07.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef __GLModelViewer__SkyBoxShader__
#define __GLModelViewer__SkyBoxShader__

#include "Shader.h"

class SkyBoxShader : public Shader {
public:
    void init();
    void setUniforms(glm::mat4& proj, glm::mat4& view, glm::mat4& model);
};

#endif /* defined(__GLModelViewer__SkyBoxShader__) */
