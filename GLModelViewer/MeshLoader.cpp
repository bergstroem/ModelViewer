//
//  MeshLoader.cpp
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-02-03.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "OFFReader.h"
#include "MeshLoader.h"
#include <stdexcept>

std::shared_ptr<Mesh> MeshLoader::loadMesh(std::string meshName) {
    std::shared_ptr<Mesh> mesh;
    
    // Lookup meshname in map
    auto it = loadedMeshes.find(meshName);
    if(it != loadedMeshes.end()) {
        // Shader found, was loaded
        auto foundMesh = it->second;
        // Create copy and assign mesh to it
        mesh = std::make_shared<Mesh>((*foundMesh.get()));
    } else {
        // Shader not found, load and add to loaded shaders
        auto loadedMesh = loadMeshFromFile(meshName);
        loadedMesh->loadBufferData();
        loadedMeshes[meshName] = loadedMesh;
        mesh = loadedMesh;
    }
    
    return mesh;
}

std::shared_ptr<Mesh> MeshLoader::loadMeshFromFile(std::string meshName) {
    std::ifstream file;
    file.open(meshName);
    
    if(!file.is_open()) {
        throw std::runtime_error("Could not open file");
        exit(EXIT_FAILURE);
    }
    
    return OFFReader::read(file);
}

MeshLoader::~MeshLoader() {
    for(auto it = loadedMeshes.begin(); it != loadedMeshes.end(); it++) {
        it->second->unloadBufferData();
    }
}
