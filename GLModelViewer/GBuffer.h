//
//  GBuffer.h
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-02-03.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef __GLModelViewer__GBuffer__
#define __GLModelViewer__GBuffer__

#include <GL/glew.h>
#include <vector>
#include "FrameBuffer.h"

class GBuffer : public FrameBuffer {
private:
    
    
public:
    void init(int width, int height);
    void init(int width, int height, std::shared_ptr<DepthAttachment> depthTexture);
};

#endif /* defined(__GLModelViewer__GBuffer__) */
