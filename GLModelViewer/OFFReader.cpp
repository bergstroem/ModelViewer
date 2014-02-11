//
//  OFFReader.cpp
//  ModelViewer
//
//  Created by Mattias Bergström on 2014-01-22.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include <string>
#include <map>
#include <list>
#include <iostream>
#include <iterator>
#include <sstream>
#include <exception>
#include <vector>
#include "glm/glm.hpp"
#include "OFFReader.h"

std::shared_ptr<Mesh> OFFReader::read(std::istream& stream) {
    
    std::map<Vertex*, std::list<glm::vec3>> normalizationInfo;
    
    std::string fileReadError = "File read error!";
    
    // Check file type
    std::string fileType;
    if(stream >> fileType && fileType != "OFF") {
        throw fileReadError + " Did not start with OFF";
    }
    
    int numVerts, numFaces, numEdges;
    if(!(stream >> numVerts >> numFaces >> numEdges)) {
        throw fileReadError + " Did not contain numVertices, numFaces and numEdges";
    }
    
    std::shared_ptr<Mesh> mesh(new Mesh);
    
    mesh->vertexBuffer.resize(numVerts);
    float x, y, z;
    for(int i = 0; i < numVerts; i++) {
        if(!(stream >> x >> y >> z)) {
            throw fileReadError + " Could not read coordinates";
        }
        Vertex vert = {{x, y, z},{0.0f,0.0f,0.0f},{1.0f,1.0f,1.0f}};
        mesh->vertexBuffer[i] = vert;
    }
    
    int numPolygonIndices;
    for (int i = 0; i < numFaces; i++) {
        // Read first col
        if(!(stream >> numPolygonIndices)) {
            throw fileReadError + " Could not read number of indices on polygon.";
        }
        
        unsigned int polygonIndices[numPolygonIndices];
        for(int j = 0; j < numPolygonIndices; j++) {
            if(!(stream >> polygonIndices[j])) {
                throw fileReadError + "Could not read polygon index";
            }
        }
        
        // Triangulate polygon
        for (int j = 2; j < numPolygonIndices; j++) {
            mesh->indexBuffer.push_back(polygonIndices[0]);
            mesh->indexBuffer.push_back(polygonIndices[j-1]);
            mesh->indexBuffer.push_back(polygonIndices[j]);
            
            
            // Create normal per triangle
            Vertex* vertex1 = &mesh->vertexBuffer[polygonIndices[0]];
            Vertex* vertex2 = &mesh->vertexBuffer[polygonIndices[j-1]];
            Vertex* vertex3 = &mesh->vertexBuffer[polygonIndices[j]];
            
            // Convert to glm vectors and create normal
            glm::vec3 vec1 = glm::vec3(vertex2->position.x - vertex1->position.x,
                                       vertex2->position.y - vertex1->position.y,
                                       vertex2->position.z - vertex1->position.z);
            glm::vec3 vec2 = glm::vec3(vertex3->position.x - vertex1->position.x,
                                       vertex3->position.y - vertex1->position.y,
                                       vertex3->position.z - vertex1->position.z);
            
            glm::vec3 triNormal = glm::cross(vec1, vec2);
            
            normalizationInfo[vertex1].push_back(triNormal);
            normalizationInfo[vertex2].push_back(triNormal);
            normalizationInfo[vertex3].push_back(triNormal);
        }
        
        // Look for color data
        std::string colorString;
        std::getline(stream, colorString);
        
        
        //Split the color string by iterating the stream
        std::istringstream colorStream(colorString);
        std::istream_iterator<std::string> begin(colorStream), end;
        std::vector<std::string> tokens(begin, end);
        
        bool isfloatColors = colorString.find(".") != std::string::npos;
        
        // Create new color stream to read form
        std::istringstream colorStream1(colorString);
        
        // We have colors!
        switch (tokens.size()) {
            case 0:
                // No colors!

                break;
            case 1:
                // TODO: Color map? What color map?!
                break;
            case 3:
            case 4:
                // Reset the color stream to read from again
                float r, g, b;
                
                // Determine if float or int
                if(isfloatColors) {
                    colorStream1 >> r >> g >> b;
                    std::cout << r << " " << g << " " << b << std::endl;
                } else {
                    // Convert from int (0-255) to float (0.0-1.0)
                    int ir, ig, ib;
                    colorStream >> ir >> ig >> ib;
                    r = ir / 255.0;
                    g = ig / 255.0;
                    b = ib / 255.0;
                }
                
                for(unsigned int& index : polygonIndices) {
                	Color color = {r, g, b};
                    mesh->vertexBuffer[index].color = color;
                }
                break;
            default:
                throw fileReadError + " Invalid number of color components.";
                break;
        }
        
    }
    
    
    //Normalize mesh
    for(auto iterator = normalizationInfo.begin(); iterator != normalizationInfo.end(); iterator++) {
        
        glm::vec3 weightedNormal;
        
        //Iterate list
        for(auto listIt = iterator->second.begin(); listIt != iterator->second.end(); listIt++) {
            weightedNormal += (*listIt);
        }
        
        weightedNormal = glm::normalize(weightedNormal);
        
        iterator->first->normal.x = weightedNormal.x;
        iterator->first->normal.y = weightedNormal.y;
        iterator->first->normal.z = weightedNormal.z;
    }
    
    return mesh;
}
