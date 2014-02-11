//
//  PerspectivePassthroughShader.cpp
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-02-05.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include "PerspectivePassthroughShader.h"
#include "ShaderLoader.h"

void PerspectivePassthroughShader::init() {
    ShaderLoader& loader = ShaderLoader::getInstance();
    
    this->programId = loader.loadShaderProgram("perspective_passthrough.vs", "perspective_passthrough.fs");
    
    this->setupBufferBindings();
}
