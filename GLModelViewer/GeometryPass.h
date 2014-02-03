//
//  GeometryPass.h
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-02-01.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef GLModelViewer_GeometryPass_h
#define GLModelViewer_GeometryPass_h

#include <vector>
#include <memory>
#include "GeometryShader.h"
#include "RenderPass.h"
#include "SceneNode.h"
#include "GBuffer.h"

class GeometryPass : public RenderPass {
    GeometryShader geometryShader;
    GBuffer* resultBuffer;
    
public:
    void init(int width, int height);
    void resize(int width, int height);
    void render(glm::mat4 proj, glm::mat4 view, std::vector<std::shared_ptr<SceneNode>> nodes);
    FrameBuffer* getBuffer();
    void bindBufferTextures();
    void unbindBufferTextures();
};

#endif
