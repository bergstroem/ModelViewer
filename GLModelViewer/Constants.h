//
//  Constants.h
//  ModelViewer
//
//  Created by Mattias Bergström on 2014-01-30.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef ModelViewer_Constants_h
#define ModelViewer_Constants_h

#include <GL/glew.h>

#define SHADER_POSITION_LOCATION 0
#define SHADER_NORMAL_LOCATION 1
#define SHADER_COLOR_LOCATION 2


enum TextureIndices {
    DIFFUSE_TEXTURE_INDEX,
    NORMAL_TEXTURE_INDEX,
    DEPTH_TEXTURE_INDEX,
    POSITION_TEXTURE_INDEX,
    AMBIENT_TEXTURE_INDEX,
    SPECULAR_TEXTURE_INDEX,
    SHININESS_TEXTURE_INDEX,
    NUM_TEXTURE_INDICES
};



#endif
