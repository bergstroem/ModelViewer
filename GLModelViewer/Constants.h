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

#ifdef __APPLE__
#define SHADER_PATH "/Users/mattiasbergstrom/Documents/src/GLModelViewer/GLModelViewer/"
#define MODEL_PATH "/Users/mattiasbergstrom/Desktop/"
#else
#define SHADER_PATH "./"
#define MODEL_PATH "../off-files/"
#endif

enum TextureIndex {
    TEXTURE_COLOR_INDEX,
    TEXTURE_DEPTH_INDEX,
    TEXTURE_NORMAL_INDEX,
    
    // Material attributes
    TEXTURE_DIFFUSE_INDEX,
    TEXTURE_AMBIENT_INDEX,
    TEXTURE_SPECULAR_INDEX,
    TEXTURE_SHININESS_INDEX,
    
    // Shadow depth
    TEXTURE_SHADOW0_INDEX,
    
    NUM_TEXTURES
};


#endif
