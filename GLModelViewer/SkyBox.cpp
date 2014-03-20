//
//  SkyBox.cpp
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-03-06.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include "SkyBox.h"
#include <glew.h>
#include <vector>
#include "MeshLoader.h"
#include "Constants.h"

#define CUBE_TEXTURE_SIZE 256

void SkyBox::init() {
    
    // Load mesh
    std::string path(MODEL_PATH);
    path.append("skybox.off");
    auto& meshLoader = MeshLoader::getInstance();
    std::shared_ptr<Mesh> mesh = meshLoader.loadMesh(path);
    
    node.init(mesh);
    node.scale = glm::scale(glm::mat4(1.0f), glm::vec3(10.f));
    node.position = glm::vec3(-5, -5, -5);
    
    createTextures();
}

void SkyBox::createTextures() {
    glGenTextures(1, &this->textureId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->textureId);
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    std::vector<char> testData(CUBE_TEXTURE_SIZE * CUBE_TEXTURE_SIZE * 256, 128);
    std::vector<char> xData(CUBE_TEXTURE_SIZE * CUBE_TEXTURE_SIZE * 256, 255);
    
    for(int loop = 0; loop < 6; ++loop)
    {
        if(loop)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + loop, 0, GL_RGB16F,
                         CUBE_TEXTURE_SIZE, CUBE_TEXTURE_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, &testData[0]);
        }
        else
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + loop, 0, GL_RGB16F,
                         CUBE_TEXTURE_SIZE, CUBE_TEXTURE_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, &xData[0]);
        }
    }
    
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void SkyBox::render() {
    glActiveTexture(GL_TEXTURE0 + TEXTURE_CUBEMAP_INDEX);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->textureId);
    
    node.render();
    
    glActiveTexture(GL_TEXTURE0 + TEXTURE_CUBEMAP_INDEX);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

}
