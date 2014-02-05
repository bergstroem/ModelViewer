//
//  ShadowBuffer.h
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-02-05.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef __GLModelViewer__ShadowBuffer__
#define __GLModelViewer__ShadowBuffer__

#include "FrameBuffer.h"

class DepthBuffer : public FrameBuffer {
public:
    void init(int width, int height);
    void init(int width, int height, std::shared_ptr<DepthAttachment> depthTexture);
};

#endif
