//
//  ModelViewerWindow.h
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-03-18.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#ifndef __GLModelViewer__ModelViewerWindow__
#define __GLModelViewer__ModelViewerWindow__

#include <iostream>
#include <string>
#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/notebook.h>
#include <gtkmm/filechooserbutton.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/entry.h>
#include "CameraMovement.h"
#include "LightProperties.h"
#include "Material.h"

class ModelViewerWindow : public Gtk::Window {
    
protected:
    //Signal handlers:
    void on_open_file_clicked();
    void on_flip_normals_clicked();
    void on_smooth_movement_clicked();
    void on_light_position_digits_changed();
    void on_light_color_digits_changed();
    
    void on_material_digits_changed();
    
    // Init functions
    void initLightWidgets();
    void initMaterialWidgets();
    void initSpinButton(Gtk::SpinButton& button);
    
    //Member widgets:
    Gtk::Box container;
    
    Gtk::Label openFileLabel;
    Gtk::Entry openFileEntry;
    Gtk::Button openFileButton;
    Gtk::Label settingsLabel;
    
    Gtk::CheckButton flipNormalsCheckButton;
    Gtk::CheckButton smoothMovement;
    Gtk::Notebook settingsNotebook;
    
    Gtk::Box lightContainer;
    Gtk::Box objectContainer;
    
    Gtk::Label lightSourcePositionLabel;
    Gtk::Label lightColorLabel;
    
    // Light Position
    Gtk::SpinButton lightXPositionSpinButton;
    Gtk::SpinButton lightYPositionSpinButton;
    Gtk::SpinButton lightZPositionSpinButton;
    
    // Light Diffuse Color
    Gtk::SpinButton lightRedColorSpinButton;
    Gtk::SpinButton lightGreenColorSpinButton;
    Gtk::SpinButton lightBlueColorSpinButton;
    
    Gtk::Label materialDiffuse;
    Gtk::Label materialAmbient;
    Gtk::Label materialSpecular;
    Gtk::Label materialShininess;
    
    // Material Diffuse
    Gtk::SpinButton diffuseRedSpinButton;
    Gtk::SpinButton diffuseGreenSpinButton;
    Gtk::SpinButton diffuseBlueSpinButton;
    
    // Material Ambient
    Gtk::SpinButton ambientRedSpinButton;
    Gtk::SpinButton ambientGreenSpinButton;
    Gtk::SpinButton ambientBlueSpinButton;
    
    // Material Specular
    Gtk::SpinButton specularRedSpinButton;
    Gtk::SpinButton specularGreenSpinButton;
    Gtk::SpinButton specularBlueSpinButton;
    
    // Material Shininess
    Gtk::SpinButton shininessSpinButton;
    
public:
    ModelViewerWindow();
    virtual ~ModelViewerWindow();
    
    CameraMovement* movement;
    LightProperties* lightProperties;
    Material* material;
    bool* flipNormals;
    bool* shouldLoadFile;
    std::string* fileName;
};

#endif /* defined(__GLModelViewer__ModelViewerWindow__) */
