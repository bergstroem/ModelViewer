//
//  MeshLoader.h
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-02-03.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef GLModelViewer_MeshLoader_h
#define GLModelViewer_MeshLoader_h

#include <map>
#include <string>
#include <memory>
#include "Mesh.h"

class MeshLoader {
    std::map<std::string, std::shared_ptr<Mesh>> loadedMeshes;
    
    // Private ctor
    MeshLoader() {};
    ~MeshLoader();
    
    // Hide copy constructor and assignment operator because singleton
    MeshLoader(MeshLoader const&);
    void operator=(MeshLoader const&);
    
    std::shared_ptr<Mesh> loadMeshFromFile(std::string meshName);
public:
    static MeshLoader& getInstance() {
        static MeshLoader instance;
        return instance;
    }
    
    std::shared_ptr<Mesh> loadMesh(std::string meshName);
};

#endif
