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
#include <memory>
#include "SceneNode.h"
#include "glm/gtc/type_ptr.hpp"

class SkyBox {
    unsigned int textureId;
    
public:
    SceneNode node;
    
    void init();
    void createTextures();
    void render();
};

#endif /* defined(__GLModelViewer__SkyBox__) */
