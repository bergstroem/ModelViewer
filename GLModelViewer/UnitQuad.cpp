//
//  TexturedScreenQuad.cpp
//  ModelViewer
//
//  Created by Mattias Bergström on 2014-01-30.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include "UnitQuad.h"
#include "Constants.h"
#include "glm/gtc/matrix_transform.hpp"

static Vertex g_quad_vertex_buffer_data[] = {
    {{-1.0f, -1.0f, 0.0f}, {0,0,0}, {0,0,0}},
    {{-1.0f, 1.0f, 0.0f}, {0,0,0}, {0,0,0}},
    {{1.0f, 1.0f, 0.0f}, {0,0,0}, {0,0,0}},
    {{1.0f, -1.0f, 0.0f}, {0,0,0}, {0,0,0}},
};


Mesh UnitQuad::CreateUnitQuad() {
    Mesh mesh;
    mesh.init(4, g_quad_vertex_buffer_data);
    mesh.indexBuffer.push_back(0);
    mesh.indexBuffer.push_back(3);
    mesh.indexBuffer.push_back(2);
    mesh.indexBuffer.push_back(0);
    mesh.indexBuffer.push_back(2);
    mesh.indexBuffer.push_back(1);
    
    mesh.loadBufferData();
    
    return mesh;
}