//
//  BloomPass.h
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-03-20.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef __GLModelViewer__BloomPass__
#define __GLModelViewer__BloomPass__

#include "RenderPass.h"
#include "ColorBuffer.h"
#include "SceneNode.h"
#include "BloomShader.h"
#include "glm/glm.hpp"

// TODO: Rewrite to take a framebuffer or texture instead of nodes
class BloomPass : public RenderPass {
    ColorBuffer* blurBuffer;
    ColorBuffer* resultBuffer;
    
    SceneNode unitQuad;
    BloomShader blurShader;
    
    void horizontalBlur();
    void verticalBlur();
public:
    ~BloomPass();
    
    void init(int width, int height);
    void resize(int width, int height);
    void render(glm::mat4 proj, glm::mat4 view, FrameBuffer* bufferToBlur);
    FrameBuffer* getBuffer();
    void bindBufferTextures();
    void unbindBufferTextures();
};
#endif /* defined(__GLModelViewer__BloomPass__) */
