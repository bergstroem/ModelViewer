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
private:
    unsigned int fbID;
    std::vector<unsigned int> colorTextureIDs;
    unsigned int depthBufferID;
    int width;
    int height;
    bool initialized;
    
    unsigned int createTextureAttachment();
    void createDepthBuffer();
    void release();

public:
    FrameBuffer();
    ~FrameBuffer();
    
    bool init(int width, int height);
    void bind();
    void unbind();
    void bindTextures();
    void unbindTextures();
    
};

#endif
