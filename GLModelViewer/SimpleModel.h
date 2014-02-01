//
//  SimpleModel.h
//  ModelViewer
//
//  Created by Mattias Bergström on 2014-01-30.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef ModelViewer_SimpleModel_h
#define ModelViewer_SimpleModel_h

#include "SceneNode.h"
#include "GeometryShader.h"

class SimpleModel : public SceneNode {
public:
    void init(std::shared_ptr<Mesh> mesh, std::shared_ptr<PhongShader> shaderProgram);
    void render(glm::mat4 proj, glm::mat4 view);
};

#endif
