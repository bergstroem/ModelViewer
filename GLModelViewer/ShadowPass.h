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
#include "DepthBuffer.h"
#include "Light.h"

class ShadowPass : public RenderPass {
    DepthBuffer* shadowBuffer;
    PerspectivePassthroughShader shader;
    int width;
    int height;
    
public:
    void render(glm::mat4 proj, glm::mat4 view, std::vector<std::shared_ptr<SceneNode>> nodes, std::vector<std::shared_ptr<Light>> lights);
    void init(int width, int height);
    void resize(int width, int height);
    FrameBuffer* getBuffer();
    void bindBufferTextures();
    void unbindBufferTextures();
};

#endif