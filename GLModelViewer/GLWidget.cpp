
#include <QtGui/QMouseEvent>
#include "GLWidget.h"
#include <iostream>
#include <fstream>
#include <memory>
#include <GLFW/glfw3.h>

#include "OFFReader.h"
#include "ShaderLoader.h"
#include "SceneRenderer.h"
#include "Constants.h"
#include "GeometryShader.h"
#include "MeshLoader.h"
#include "LightProperties.h"
#include "Light.h"

#include "glm/glm.hpp"
#include <cmath>
#include "Mesh.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


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

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent) {
    setMouseTracking(true);
}

GLWidget::GLWidget(const QGLFormat & format, QWidget * parent) : QGLWidget(format, parent) {
    setMouseTracking(true);
}

void GLWidget::initializeGL() {

    // Initialize GLEW
    glewExperimental=true; // Needed in core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        exit(EXIT_FAILURE);
    }

    renderer.init(this->width(), this->height());

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
    
    lastTime = glfwGetTime();
    
    for(int i = 0; i < 2; i++) {
        std::string path(MODEL_PATH);
        path.append("cooldragon.off");
        auto node = createSceneNode(path);
        node->position = glm::vec3(-2.0f, -0.5f, -3.0f * (i + 1));
        
        renderer.nodes.push_back(node);
    }
    
    renderer.nodes.push_back(floor);
}

void GLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h); // set origin to bottom left corner
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    float ratio = this->width() / (float)this->height();
    
    //light->properties.position = glm::translate(glm::mat4(1.0f), glm::vec3(-2.5f +  cosf(0.0/*glfwGetTime()*/), 0.5f, -0.0f)) * glm::vec4(1.0f);
    
    renderer.proj = glm::perspective(60.0f, ratio, 0.1f, 1000.0f);
    
    // Rotation Up/Down
    renderer.view = glm::rotate(glm::mat4(1.0f), rotationPitch, glm::vec3(1.0f, 0.0f, 0.0f));
    
    // Rotation around Y
    renderer.view = glm::rotate(renderer.view, rotationY, glm::vec3(0.0f, 1.0f, 0.0f));
    renderer.view = glm::translate(renderer.view, move);
    
    renderer.renderScene();
}

void GLWidget::mousePressEvent(QMouseEvent *event) {

}
void GLWidget::mouseMoveEvent(QMouseEvent *event) {
    printf("%d, %d\n", event->x(), event->y());
}

void GLWidget::keyPressEvent(QKeyEvent* event) {
    switch(event->key()) {
    case Qt::Key_Escape:
        close();
        break;
    default:
        event->ignore();
        break;
    }
}