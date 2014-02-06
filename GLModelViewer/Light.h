//
//  Light.h
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-02-06.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef __GLModelViewer__Light__
#define __GLModelViewer__Light__

#include <memory>
#include "LightProperties.h"
#include "DepthAttachment.h"

class Light {
public:
    LightProperties properties;
    std::shared_ptr<DepthAttachment> shadowTexture;
    
    
};

#endif 
