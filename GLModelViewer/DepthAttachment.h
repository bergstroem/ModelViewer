//
//  DepthAttachment.h
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-02-04.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef __GLModelViewer__DepthAttachment__
#define __GLModelViewer__DepthAttachment__

class DepthAttachment {
    
public:
    unsigned int textureId;
    int width;
    int height;
    
    ~DepthAttachment();
    
    void init(int width, int height);
    void bind();
    void unbind();
};

#endif 
