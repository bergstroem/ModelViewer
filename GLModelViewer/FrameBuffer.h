//
//  FrameBuffer.h
//  ModelViewer
//
//  Created by Mattias Bergström on 2014-01-30.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef ModelViewer_FrameBuffer_h
#define ModelViewer_FrameBuffer_h

#include <GL/glew.h>
#include <vector>

class FrameBuffer {
protected:
    unsigned int fbID;
    unsigned int depthTextureID;
    int width;
    int height;
    bool initialized;
    
    unsigned int createTextureAttachment();
    void createDepthBuffer();

public:
    virtual ~FrameBuffer();
    
    virtual bool init(int width, int height) = 0;
    virtual bool init(int width, int height, unsigned int depthTexId) = 0;
    void bind();
    void unbind();
    virtual void bindTextures() = 0;
    virtual void unbindTextures() = 0;
    
};

#endif
