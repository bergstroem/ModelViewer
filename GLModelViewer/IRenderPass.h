//
//  RenderPass.h
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-01-31.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef GLModelViewer_RenderPass_h
#define GLModelViewer_RenderPass_h

#include <vector>
#include <glm/glm.hpp>
#include "SceneNode.h"

class IRenderPass {
    
public:
    virtual void init(int width, int height) = 0;
    virtual void resize(int width, int height) = 0;
    // TODO: CHANGE INTO SINGLE NODE WHEN NODES START TO HAVE CHILDREN
    virtual void render(glm::mat4 proj, glm::mat4 view, std::vector<std::shared_ptr<SceneNode>> nodes) = 0;
};

#endif
