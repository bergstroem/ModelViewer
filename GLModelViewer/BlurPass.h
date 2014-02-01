//
//  BlurPass.h
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-01-31.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef GLModelViewer_BlurPass_h
#define GLModelViewer_BlurPass_h

#include "IRenderPass.h"
#include "FrameBuffer.h"
#include "SceneNode.h"
#include "BlurShader.h"

class BlurPass : public IRenderPass {
    FrameBuffer* pass1Buffer;
    FrameBuffer* pass2Buffer;
    SceneNode unitQuad;
    
    std::shared_ptr<BlurShader> blurShader;
    
    void horizontalBlur();
    void verticalBlur();
public:
    ~BlurPass();
    
    void init(int width, int height);
    void resize(int width, int height);
    void render(glm::mat4 proj, glm::mat4 view, std::vector<std::shared_ptr<SceneNode>> nodes);
};

#endif
