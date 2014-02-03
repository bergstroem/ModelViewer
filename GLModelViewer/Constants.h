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

#define SHADER_POSITION_LOCATION    0
#define SHADER_NORMAL_LOCATION      1
#define SHADER_COLOR_LOCATION       2

enum TextureIndices {
    TEXTURE_NORMAL_INDEX,
    TEXTURE_POSITION_INDEX,
    
    // Material
    TEXTURE_DIFFUSE_INDEX,
    TEXTURE_AMBIENT_INDEX,
    TEXTURE_SPECULAR_INDEX,
    TEXTURE_SHININESS_INDEX,
    NUM_TEXTURES
};

//Not counted, handled separately
#define TEXTURE_DEPTH_INDEX 8



#endif
