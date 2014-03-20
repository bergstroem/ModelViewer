//
//  HDRPass.h
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-03-20.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef __GLModelViewer__HDRPass__
#define __GLModelViewer__HDRPass__

#include <iostream>
#include "RenderPass.h"
#include "ColorBuffer.h"
#include "ToneMappingShader.h"
#include "PassthroughShader.h"
#include "BloomPass.h"

class HDRPass : public RenderPass {
    BloomPass bloomPass;
    ToneMappingShader toneMapping;
    PassthroughShader passthrough;
    SceneNode unitQuad;
    ColorBuffer* resultBuffer;
    
    int width;
    int height;
    
public:
    void init(int width, int height);
    void init(int width, int height, std::shared_ptr<DepthAttachment> depthTexture);
    void resize(int width, int height);
    void resize(int width, int height, std::shared_ptr<DepthAttachment> depthTexture);
    void render(glm::mat4 proj, glm::mat4 view, ColorBuffer* buffer, float exposure);
    FrameBuffer* getBuffer();
    void bindBufferTextures();
    void unbindBufferTextures();
};

#endif /* defined(__GLModelViewer__HDRPass__) */
