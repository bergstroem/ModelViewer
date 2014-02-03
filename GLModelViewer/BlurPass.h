//
//  BlurPass.h
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-01-31.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef GLModelViewer_BlurPass_h
#define GLModelViewer_BlurPass_h

#include "RenderPass.h"
#include "ColorBuffer.h"
#include "SceneNode.h"
#include "BlurShader.h"
#include "glm/glm.hpp"

// TODO: Rewrite to take a framebuffer or texture instead of nodes
class BlurPass : public RenderPass {
    ColorBuffer* blurBuffer;
    ColorBuffer* resultBuffer;
    
    SceneNode unitQuad;
    BlurShader blurShader;
    
    void horizontalBlur();
    void verticalBlur();
public:
    ~BlurPass();
    
    void init(int width, int height);
    void resize(int width, int height);
    void render(glm::mat4 proj, glm::mat4 view, FrameBuffer* bufferToBlur);
    FrameBuffer* getBuffer();
    void bindBufferTextures();
    void unbindBufferTextures();
};

#endif
