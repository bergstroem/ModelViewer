//
//  PassthroughShader.h
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-02-03.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef GLModelViewer_PassthroughShader_h
#define GLModelViewer_PassthroughShader_h

#include "Shader.h"

class PassthroughShader : public Shader {
public:
    void init();
    void setUniforms(glm::mat4& proj, glm::mat4& view, glm::mat4& model);
};


#endif
