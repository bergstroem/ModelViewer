//
//  Mesh.h
//  ModelViewer
//
//  Created by Mattias Bergström on 2014-01-22.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef ModelViewer_Mesh_h
#define ModelViewer_Mesh_h

#include <vector>
#include <GL/glew.h>
#include "Constants.h"
#include "Material.h"

struct Vector3 {
    float x;
    float y;
    float z;
};

struct Color {
    float r;
    float g;
    float b;
};

struct Vertex {
    Vector3 position;
    Vector3 normal;
    Color color;
};

/*
 * A simple class containing the vertex and index buffer, can upload buffers to gpu
 */
class Mesh {
public:
    std::vector<Vertex> vertexBuffer;
    std::vector<unsigned int> indexBuffer;
    
    unsigned int bufferId;
    unsigned int indexId;
    unsigned int vaoId;
    
    Material material;
    
    void init(std::size_t numVertices, Vertex* vertexData);
    void loadBufferData();
    void unloadBufferData();
    
    void bind();
    void unbind();
};

#endif
