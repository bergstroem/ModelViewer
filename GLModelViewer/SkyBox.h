//
//  SkyBox.h
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-03-06.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef __GLModelViewer__SkyBox__
#define __GLModelViewer__SkyBox__

#include "Mesh.h"

class SkyBox {
    unsigned int textureId;
    Mesh mesh;
public:
    
    void init();
    void createTextures();
    
};

#endif /* defined(__GLModelViewer__SkyBox__) */
