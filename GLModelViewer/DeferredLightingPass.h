//
//  DeferredLightingPass.h
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-02-05.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef __GLModelViewer__DeferredLightingPass__
#define __GLModelViewer__DeferredLightingPass__

#include "RenderPass.h"
#include "GBuffer.h"
#include "SceneNode.h"
#include "ColorBuffer.h"
#include "DeferredPhongShader.h"
#include "Light.h"
#include "ShadowPass.h"

class DeferredLightingPass : public RenderPass {
    ShadowPass shadowPass;
    DeferredPhongShader deferredPhong;
    SceneNode unitQuad;
    ColorBuffer* resultBuffer;
    int width;
    int height;
    
public:
    void init(int width, int height);
    void init(int width, int height, std::shared_ptr<DepthAttachment> depthTexture);
    void resize(int width, int height);
    void resize(int width, int height, std::shared_ptr<DepthAttachment> depthTexture);
    void render(glm::mat4 proj, glm::mat4 view, GBuffer* gBuffer, std::vector<std::shared_ptr<SceneNode>> nodes, std::vector<std::shared_ptr<Light>> lights);
    FrameBuffer* getBuffer();
    void bindBufferTextures();
    void unbindBufferTextures();
};

#endif
