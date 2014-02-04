//
//  DepthTexture.h
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-02-04.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef __GLModelViewer__DepthTexture__
#define __GLModelViewer__DepthTexture__

class DepthTexture {
    unsigned int texId;
    
public:
    
    void init(int width, int height);
    void resize(int width, int height);
};

#endif 
