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
    unsigned int colorTextureID;
    
    void release();
    
public:
    ColorBuffer();
    ~ColorBuffer();
    
    bool init(int width, int height);
    bool init(int width, int height, unsigned int depthTexId);
    void bindTextures();
    void unbindTextures();
    
};

#endif 
