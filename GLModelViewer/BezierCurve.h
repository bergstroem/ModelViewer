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


class BezierCurve {
public:
    glm::vec3 startPoint;
    glm::vec3 controlPoint;
    glm::vec3 endPoint;
    
    glm::vec3 getPosition(float t);
};

#endif /* defined(__GLModelViewer__BezierCurve__) */
