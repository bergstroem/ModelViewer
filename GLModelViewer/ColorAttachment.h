//
//  ColorAttachment.h
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-02-04.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef __GLModelViewer__ColorAttachment__
#define __GLModelViewer__ColorAttachment__

#include "Constants.h"

class ColorAttachment {
public:
    TextureIndex index;
    unsigned int textureId;
    int width;
    int height;
    
    ~ColorAttachment();
    
    void init(int width, int height, TextureIndex index);
    void bind();
    void unbind();
};

#endif
