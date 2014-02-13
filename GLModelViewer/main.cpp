//
//  main.cpp
//  ModelViewer
//
//  Created by Mattias Bergström on 2014-01-21.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "glm/glm.hpp"
#include <cmath>
#include "Mesh.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

#include "OFFReader.h"
#include "ShaderLoader.h"
#include "SceneRenderer.h"
#include "Constants.h"
#include "GeometryShader.h"
#include "MeshLoader.h"
#include "LightProperties.h"

SceneRenderer renderer;
glm::vec3 move;
float rotationY = 0.0f;
float rotationPitch = 0.0f;
float lastTime = 0.0;

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    
    if(key == GLFW_KEY_U && action == GLFW_PRESS) {
        renderer.isDeferred = !renderer.isDeferred;

        std::cout << "Deferred " << renderer.isDeferred << std::endl;
    }
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    renderer.updateResolution(width, height);
}

void updateInput(GLFWwindow* window) {
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);
    
    glm::vec3 velocity;
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        velocity.z += cosf(rotationY * M_PI / 180);
        velocity.x -= sinf(rotationY * M_PI / 180);
        
    } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        velocity.z -= cosf(rotationY * M_PI / 180);
        velocity.x += sinf(rotationY * M_PI / 180);
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        velocity.z += sinf(rotationY * M_PI / 180);
        velocity.x += cosf(rotationY * M_PI / 180);
    } else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        velocity.z -= sinf(rotationY * M_PI / 180);
        velocity.x -= cosf(rotationY * M_PI / 180);
    }
    
    if(glm::length(velocity) > 0) {
        velocity = glm::normalize(velocity)* 4.0f;
        
        move += velocity * deltaTime;
    }
    
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        rotationY -= 100.0f * deltaTime;
    } else if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        rotationY += 100.0f * deltaTime;
    }
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        rotationPitch -= 100.0f * deltaTime;
    } else if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        rotationPitch += 100.0 * deltaTime;
    }
    
    lastTime = currentTime;
}

void initGL() {
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

GLFWwindow* initGLWindow() {
    GLFWwindow* window;
    
    
    glfwSetErrorCallback(error_callback);
    
    if (!glfwInit())
        exit(EXIT_FAILURE);
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(854, 480, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    // Initialize GLEW
    glewExperimental=true; // Needed in core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        exit(EXIT_FAILURE);
    }
    
    return window;
}

std::shared_ptr<SceneNode> createSceneNode(std::string meshName) {
    auto& meshLoader = MeshLoader::getInstance();
    std::shared_ptr<Mesh> mesh = meshLoader.loadMesh(meshName);

    auto node = std::shared_ptr<SceneNode>(new SceneNode());
    mesh->material.diffuse = glm::vec4(0.5f, 0.5f, 0.7f, 1.0f);
    mesh->material.ambient = glm::vec4(0.01f, 0.01f, 0.01f, 1.0f);
    mesh->material.specular = glm::vec4(0.6f, 0.6f, 0.7f, 1.0f);
    mesh->material.shininess = 250.0f;
    
    node->init(mesh);
    
    return node;
}

int main()
{
    GLFWwindow* window = initGLWindow();
    
    initGL();
    
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    
    //Floor
    std::shared_ptr<Mesh> floorMesh = std::make_shared<Mesh>(UnitQuad::CreateUnitQuad());
    floorMesh->material.diffuse = glm::vec4(0.3f, 0.6f, 0.7f, 1.0f);
    floorMesh->material.ambient = glm::vec4(0.01f, 0.01f, 0.01f, 1.0f);
    floorMesh->material.specular = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
    floorMesh->material.shininess = 100.0f;
    
    std::shared_ptr<SceneNode> floor(new SceneNode);
    floor->init(floorMesh);
    floor->position = glm::vec3(0.0,-1.0, 0.0);
    floor->rotation = glm::rotate(glm::mat4(1.0f),-90.0f, glm::vec3(1.0, 0.0, 0.0));
    floor->scale = glm::scale(glm::mat4(1.0), glm::vec3(100.0f));
    
    LightProperties lightProperties = LightFactory::Bright(glm::vec3(0.8, 0.9, 1.0));
    lightProperties.position = glm::vec4(-2.0f, 2.0f, -1.0f, 1.0);
    lightProperties.direction = glm::vec4(0.0, -0.1, -1.0, 0.0);
    std::shared_ptr<Light> light(new Light);
    light->properties = lightProperties;
    renderer.lights.push_back(light);
    
    LightProperties lightProperties1 = LightFactory::Bright(glm::vec3(0.8, 0.9, 1.0));
    lightProperties1.position = glm::vec4(4.0f, 2.0f, -3.0f, 1.0);
    lightProperties1.direction = glm::vec4(-1.0, -0.1, 0.0, 0.0);
    std::shared_ptr<Light> light1(new Light);
    light1->properties = lightProperties1;
    renderer.lights.push_back(light1);
    
    renderer.init(width, height);
    
    lastTime = glfwGetTime();
    
    for(int i = 0; i < 2; i++) {
        std::string path(MODEL_PATH);
        path.append("cooldragon.off");
        auto node = createSceneNode(path);
        node->position = glm::vec3(-2.0f, -0.5f, -3.0f * (i + 1));
        
        renderer.nodes.push_back(node);
    }
    
    renderer.nodes.push_back(floor);
    
    glfwSwapInterval(1); //0 to disable vsync, 1 to enable it

    
    while (!glfwWindowShouldClose(window))
    {
        updateInput(window);
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        
        glfwGetFramebufferSize(window, &width, &height);
        float ratio = width / (float)height;
        
        light->properties.position = glm::translate(glm::mat4(1.0f), glm::vec3(-2.5f +  cosf(glfwGetTime()), 0.5f, -0.0f)) * glm::vec4(1.0f);
        
        renderer.proj = glm::perspective(60.0f, ratio, 0.1f, 1000.0f);
        
        // Rotation Up/Down
        renderer.view = glm::rotate(glm::mat4(1.0f), rotationPitch, glm::vec3(1.0f, 0.0f, 0.0f));
        
        // Rotation around Y
        renderer.view = glm::rotate(renderer.view, rotationY, glm::vec3(0.0f, 1.0f, 0.0f));
        renderer.view = glm::translate(renderer.view, move);
        
        renderer.renderScene();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

