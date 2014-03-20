//
//  BezierCurve.cpp
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-03-05.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include "BezierCurve.h"
#include "MathHelper.h"

glm::vec3 BezierCurve::getPosition(float t) {
    t = CLAMP(t, 0.0f, 1.0f);
    return (1 - t) * ((1 - t) * startPoint + t * controlPoint) + t * ((1 - t) * controlPoint + t * endPoint);
}
