//
//  ColorBuffer.h
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-02-03.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef __GLModelViewer__ColorBuffer__
#define __GLModelViewer__ColorBuffer__

#include <GL/glew.h>
#include <vector>
#include "FrameBuffer.h"

class ColorBuffer : public FrameBuffer {
protected:
    
public:
    void init(int width, int height);
    void init(int width, int height, std::shared_ptr<DepthAttachment> depthTexture);
};

#endif 
