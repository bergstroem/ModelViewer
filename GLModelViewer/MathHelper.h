//
//  MathHelper.h
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-03-05.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef GLModelViewer_MathHelper_h
#define GLModelViewer_MathHelper_h

template <typename T> T CLAMP(const T& value, const T& low, const T& high)
{
    return value < low ? low : (value > high ? high : value);
}

#endif
