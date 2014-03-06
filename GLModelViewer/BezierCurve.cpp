//
//  BezierCurve.cpp
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-03-05.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include "BezierCurve.h"

glm::vec4 BezierCurve::getPosition(float t) {
    t = CLAMP(t, 0.f, 1.f);
    return (1 - t) * ((1 - t) * startPoint + t * controlPoint) + t * ((1 - t) * controlPoint + t * endPoint);
}