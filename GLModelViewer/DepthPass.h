//
//  DepthPass.h
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-02-05.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef __GLModelViewer__DepthPass__
#define __GLModelViewer__DepthPass__

#include "RenderPass.h"
#include "DepthBuffer.h"
#include "PerspectivePassthroughShader.h"

class DepthPass : public RenderPass {
    DepthBuffer* depthBuffer;
    PerspectivePassthroughShader passtroughShader;
public:
    void init(int width, int height);
    void resize(int width, int height);
    void render(glm::mat4 proj, glm::mat4 view, std::vector<std::shared_ptr<SceneNode>> nodes);
    FrameBuffer* getBuffer();
    void bindBufferTextures();
    void unbindBufferTextures();
};

#endif
