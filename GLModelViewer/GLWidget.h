//
//  BlurPass.h
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-01-31.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef GLModelViewer_GLWidget_h
#define GLModelViewer_GLWidget_h

#include <GL/glew.h>
#include <QtOpenGL/QGLWidget>

#include "SceneRenderer.h"


class GLWidget : public QGLWidget {
    //Q_OBJECT // must include this if you use Qt signals/slots

private:
    SceneRenderer renderer;
    glm::vec3 move;
    float rotationY = 0.0f;
    float rotationPitch = 0.0f;
    float lastTime = 0.0;

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
public:
    GLWidget(QWidget *parent = NULL);
    GLWidget(const QGLFormat & format, QWidget * parent = 0);
};

#endif
