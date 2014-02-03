//
//  RenderPass.h
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-01-31.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef GLModelViewer_RenderPass_h
#define GLModelViewer_RenderPass_h

#include <vector>
#include <glm/glm.hpp>
#include "SceneNode.h"
#include "FrameBuffer.h"

/*
 * Abstract class for render passes
 */
class RenderPass {
    
public:
    
    virtual void init(int width, int height) = 0;
    virtual void resize(int width, int height) = 0;
    virtual FrameBuffer* getBuffer() = 0;
    virtual void bindBufferTextures() = 0;
    virtual void unbindBufferTextures() = 0;
};

#endif
