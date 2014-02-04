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
#include <memory>
#include "ColorAttachment.h"
#include "DepthAttachment.h"

class FrameBuffer {
protected:
    unsigned int fboId;
    int width;
    int height;
    
    // Attachments
    std::vector<std::shared_ptr<ColorAttachment>> colorAttachments;
    std::shared_ptr<DepthAttachment> depthAttachment;
    
    // Methods
    void updateDrawBuffers();
    
    
public:
    FrameBuffer();
    virtual ~FrameBuffer();
    
    virtual void init(int width, int height) = 0;
    void bind();
    void unbind();
    
    // Color attachments
    void attachColorTexture(std::shared_ptr<ColorAttachment> colorTexture);
    void detachColorTexture(std::shared_ptr<ColorAttachment> colorTexture);
    std::vector<std::shared_ptr<ColorAttachment>> getColorAttachments();
    
    // Depth attachment
    void setDepthAttachment(std::shared_ptr<DepthAttachment> depthTexture);
    std::shared_ptr<DepthAttachment> getDepthAttachment();
    
    void bindAttachments();
    void unbindAttachments();
};

#endif
