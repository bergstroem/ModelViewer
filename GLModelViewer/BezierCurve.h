//
//  BezierCurve.h
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-03-05.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef __GLModelViewer__BezierCurve__
#define __GLModelViewer__BezierCurve__

#include "glm/gtc/type_ptr.hpp"
#include "MathHelper.h"

class BezierCurve {
public:
    glm::vec4 startPoint;
    glm::vec4 controlPoint;
    glm::vec4 endPoint;
    
    glm::vec4 getPosition(float t);
};

#endif /* defined(__GLModelViewer__BezierCurve__) */
