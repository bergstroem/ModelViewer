//
//  GeometryShader.h
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-02-01.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef GLModelViewer_GeometryShader_h
#define GLModelViewer_GeometryShader_h

#include "Shader.h"
#include "Material.h"

class GeometryShader : public Shader {
    
public:
    void setMaterial(Material material);
    void init();
    void setUniforms(glm::mat4& proj, glm::mat4& view, glm::mat4& model);
};

#endif
