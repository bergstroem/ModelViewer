//
//  ShaderLoader.h
//  ModelViewer
//
//  Created by Mattias Bergström on 2014-01-27.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef ModelViewer_ShaderLoader_h
#define ModelViewer_ShaderLoader_h

#include <map>
#include <string>
#include <GL/glew.h>

class ShaderLoader {
private:
    std::map<std::string, unsigned int> loadedVertexShaders;
    std::map<std::string, unsigned int> loadedFragmentShaders;
    
    // Private ctor
    ShaderLoader() {};
    
    // Don't want copy constructor and assignment operator accessible.
    ShaderLoader(ShaderLoader const&);
    void operator=(ShaderLoader const&);
    
    int loadVertexShader(std::string vertexShader);
    int loadFragmentShader(std::string fragmentShader);
    int loadShader(GLenum shaderType, std::string shader);
    bool shaderStatusOK(int shaderId);
    
public:
    static ShaderLoader& getInstance()
    {
        static ShaderLoader instance;
        return instance;
    }
    
    int loadShaderProgram(std::string vertexShader, std::string fragmentShader);
};

#endif
