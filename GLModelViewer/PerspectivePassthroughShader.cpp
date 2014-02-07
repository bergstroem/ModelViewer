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
    
    this->programId = loader.loadShaderProgram("/Users/mattiasbergstrom/Documents/src/GLModelViewer/GLModelViewer/perspective_passthrough.vs", "/Users/mattiasbergstrom/Documents/src/GLModelViewer/GLModelViewer/perspective_passthrough.fs");
    
    this->setupBufferBindings();
}
