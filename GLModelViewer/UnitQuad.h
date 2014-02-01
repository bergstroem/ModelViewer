//
//  TexturedScreenQuad.h
//  ModelViewer
//
//  Created by Mattias Bergström on 2014-01-30.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef ModelViewer_TexturedScreenQuad_h
#define ModelViewer_TexturedScreenQuad_h

#include <GL/glew.h>
#include "BlurShader.h"
#include "SceneNode.h"
#include "glm/glm.hpp"

/* Draws a textured quad to screen
 */
class UnitQuad {
    
    
public:
    static Mesh CreateUnitQuad();
};

#endif
