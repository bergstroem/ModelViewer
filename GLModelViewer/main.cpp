//
//  main.cpp
//  ModelViewer
//
//  Created by Mattias Bergström on 2014-01-21.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include <iostream>
#include <thread>
#include "glm/glm.hpp"
#include <cmath>
#include "Mesh.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "SceneRenderer.h"
#include "Constants.h"
#include "MeshLoader.h"
#include "LightProperties.h"
#include "CameraMovement.h"
#include "ModelViewerWindow.h"
#include <glew.h>
#include <GLFW/glfw3.h>
#include <gtkmm/application.h>

#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

CameraMovement* movement;
Camera camera;
SceneRenderer renderer;
bool shouldFlipNormals = false;
bool shouldLoadFile = false;
std::string filename = "cooldragon.off";
ModelViewerWindow* gui;

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    
    if(key == GLFW_KEY_1 && action == GLFW_PRESS) {
        camera.setCameraProjection(PROJECTION_PERSPECTIVE);
    }
    if(key == GLFW_KEY_2 && action == GLFW_PRESS) {
        camera.setCameraProjection(PROJECTION_ORTHOGONAL);
    }
    if(key == GLFW_KEY_3 && action == GLFW_PRESS) {
        camera.setCameraProjection(PROJECTION_OBLIQUE);
    }
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    renderer.updateResolution(width, height);
}

void updateInput(GLFWwindow* window) {
    
    movement->update();
}

void initGL() {
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

int startGui(int argc, char** argv) {
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.modelviewer");
    
    gui = new ModelViewerWindow();
    gui->movement = movement;
    gui->lightProperties = &renderer.lights[1]->properties;
    gui->material = &renderer.nodes[0]->mesh->material;
    gui->flipNormals = &shouldFlipNormals;
    gui->fileName = &filename;
    gui->shouldLoadFile = &shouldLoadFile;
    gui->exposure = &renderer.exposure;
    
    //Shows the window and returns when it is closed.
    return app->run(*gui);
}

int main(int argc, char** argv)
{
    GLFWwindow* window = initGLWindow();
    
    movement = new CameraMovement(window);
    
    initGL();
    
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    renderer.init(width, height);
    
    camera.init(width/(float)height, 60.f, .1f, 100.f);
    camera.setCameraProjection(PROJECTION_PERSPECTIVE);
    
    // Floor
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
    
    for(int i = 0; i < 1; i++) {
        std::string path(MODEL_PATH);
        path.append("cooldragon.off");
        auto node = createSceneNode(path);
        node->position = glm::vec3(-2.0f, -0.5f, -3.0f * (i + 1));
        
        renderer.nodes.push_back(node);
    }
    
    renderer.nodes.push_back(floor);
    
    std::thread first (startGui, argc, argv);
    
    glfwSwapInterval(1); //0 to disable vsync, 1 to enable it
    
    while (!glfwWindowShouldClose(window))
    {
        if(shouldFlipNormals) {
            renderer.nodes[0]->mesh->flipNormals();
            shouldFlipNormals = false;
        }
        
        if(shouldLoadFile) {
            auto& meshLoader = MeshLoader::getInstance();
            std::string path(MODEL_PATH);
            path.append(filename);
            renderer.nodes[0] = createSceneNode(path);
            renderer.nodes[0]->position = glm::vec3(-2.0f, -0.5f, -3.0f);
            
            gui->material = &renderer.nodes[0]->mesh->material;
            shouldLoadFile = false;
        }
        
        updateInput(window);
        
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glClearColor(0.0, 0.0, 0.0, 0.0);
        
        light->properties.position = glm::translate(glm::mat4(1.0f), glm::vec3(-2.5f +  cosf(glfwGetTime()), 0.5f, -0.0f)) * glm::vec4(1.0f);
        
        
        camera.position = movement->position;
        camera.target = camera.position + movement->lookatDirection;
        camera.update();
        
        renderer.proj = camera.getCameraProjectionTransform();
        renderer.view = camera.getCameraViewTransform();
        renderer.renderScene();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    delete movement;
    
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
