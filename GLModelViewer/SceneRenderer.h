//
//  SceneRenderer.h
//  ModelViewer
//
//  Created by Mattias Bergström on 2014-01-28.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef ModelViewer_SceneRenderer_h
#define ModelViewer_SceneRenderer_h

#include <deque>
#include "glm/glm.hpp"
#include "UnitQuad.h"
#include "FrameBuffer.h"
#include "BlurPass.h"
#include "GeometryPass.h"
#include "LightingPass.h"

class SceneRenderer {
    GeometryPass geometryPass;
    LightingPass lightingPass;
    
public:
    glm::mat4 proj;
    glm::mat4 view;
    std::vector<std::shared_ptr<SceneNode>> nodes;
    
    void init(int width, int height);
    void updateResolution(int width, int height);
    void renderScene();
};

#endif
