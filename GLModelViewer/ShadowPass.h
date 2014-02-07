//
//  ShadowPass.h
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-02-05.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef __GLModelViewer__ShadowPass__
#define __GLModelViewer__ShadowPass__

#include "RenderPass.h"
#include "PerspectivePassthroughShader.h"
#include "Light.h"
#include "DepthBuffer.h"

class ShadowPass : public RenderPass {
    // TODO: Make this a collection of buffers
    DepthBuffer* shadowBuffer;
    PerspectivePassthroughShader shader;
    int width;
    int height;
    
public:
    void render(glm::mat4 proj, glm::mat4 view, std::vector<std::shared_ptr<SceneNode>> nodes, std::shared_ptr<Light> light);
    void init(int width, int height);
    void resize(int width, int height);
    FrameBuffer* getBuffer();
    void bindBufferTextures();
    void unbindBufferTextures();
};

#endif
