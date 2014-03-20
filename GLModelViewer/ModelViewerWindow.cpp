//
//  ModelViewerWindow.cpp
//  GLModelViewer
//
//  Created by Mattias Bergström on 2014-03-18.
//  Copyright (c) 2014 Mattias Bergström. All rights reserved.
//

#include "ModelViewerWindow.h"



ModelViewerWindow::ModelViewerWindow()   // creates a new button with label "Hello World".
{
    // Sets the border width of the window.
    set_border_width(10);
    
    // Create container
    container.set_orientation(Gtk::ORIENTATION_VERTICAL);
    container.set_homogeneous(false);
    container.set_halign(Gtk::ALIGN_START);
    container.show();
    
    // Open file
    openFileEntry.show();
    openFileLabel.set_text("Open");
    openFileLabel.set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_START);
    openFileLabel.show();
    
    openFileButton.signal_clicked().connect(sigc::mem_fun(*this, &ModelViewerWindow::on_open_file_clicked));
    openFileButton.set_label("Open File");
    openFileButton.show();
    
    // Settings
    settingsLabel.set_text("Settings");
    settingsLabel.set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_START);
    settingsLabel.show();
    
    smoothMovement.set_label("Use Smooth Movement");
    smoothMovement.set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_START);
    smoothMovement.signal_clicked().connect(sigc::mem_fun(*this, &ModelViewerWindow::on_smooth_movement_clicked));
    smoothMovement.show();
    
    
    flipNormalsCheckButton.set_label("Flip normals");
    flipNormalsCheckButton.set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_START);
    flipNormalsCheckButton.signal_clicked().connect(sigc::mem_fun(*this, &ModelViewerWindow::on_flip_normals_clicked));
    flipNormalsCheckButton.show();
    
    settingsNotebook.show();
    
    
    initLightWidgets();
    
    // Object settings
    initMaterialWidgets();
    
    // Insert widgets
    container.pack_start(openFileLabel, Gtk::PACK_SHRINK);
    container.pack_start(openFileEntry, Gtk::PACK_SHRINK);
    container.pack_start(openFileButton, Gtk::PACK_SHRINK);
    container.pack_start(settingsLabel, Gtk::PACK_SHRINK);
    container.pack_start(smoothMovement, Gtk::PACK_SHRINK);
    container.pack_start(flipNormalsCheckButton, Gtk::PACK_SHRINK);
    container.pack_start(settingsNotebook);
    settingsNotebook.add(lightContainer);
    settingsNotebook.add(objectContainer);
    settingsNotebook.set_tab_label_text(lightContainer, "Light Settings");
    settingsNotebook.set_tab_label_text(objectContainer, "Object Settings");
    
    add(container);
}

void ModelViewerWindow::initLightWidgets() {
    lightContainer.set_orientation(Gtk::ORIENTATION_VERTICAL);
    lightContainer.show();
    
    lightSourcePositionLabel.set_text("Light Source Position");
    lightSourcePositionLabel.set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_START);
    lightSourcePositionLabel.show();
    
    
    initSpinButton(lightXPositionSpinButton);
    initSpinButton(lightYPositionSpinButton);
    initSpinButton(lightZPositionSpinButton);
    lightXPositionSpinButton.signal_value_changed().connect( sigc::mem_fun(*this, &ModelViewerWindow::on_light_position_digits_changed) );
    lightYPositionSpinButton.signal_value_changed().connect( sigc::mem_fun(*this, &ModelViewerWindow::on_light_position_digits_changed) );
    lightZPositionSpinButton.signal_value_changed().connect( sigc::mem_fun(*this, &ModelViewerWindow::on_light_position_digits_changed) );
    
    
    lightColorLabel.set_text("Light Color");
    lightColorLabel.set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_START);
    lightColorLabel.show();
    
    initSpinButton(lightRedColorSpinButton);
    initSpinButton(lightGreenColorSpinButton);
    initSpinButton(lightBlueColorSpinButton);
    lightRedColorSpinButton.signal_value_changed().connect( sigc::mem_fun(*this, &ModelViewerWindow::on_light_color_digits_changed) );
    lightGreenColorSpinButton.signal_value_changed().connect( sigc::mem_fun(*this, &ModelViewerWindow::on_light_color_digits_changed) );
    lightBlueColorSpinButton.signal_value_changed().connect( sigc::mem_fun(*this, &ModelViewerWindow::on_light_color_digits_changed) );
    
    lightContainer.add(lightSourcePositionLabel);
    lightContainer.add(lightXPositionSpinButton);
    lightContainer.add(lightYPositionSpinButton);
    lightContainer.add(lightZPositionSpinButton);
    
    lightContainer.add(lightColorLabel);
    lightContainer.add(lightRedColorSpinButton);
    lightContainer.add(lightGreenColorSpinButton);
    lightContainer.add(lightBlueColorSpinButton);
}

void ModelViewerWindow::initMaterialWidgets() {
    objectContainer.set_orientation(Gtk::ORIENTATION_VERTICAL);
    objectContainer.show();
    
    materialDiffuse.set_text("Diffuse");
    materialDiffuse.set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_START);
    materialDiffuse.show();
    
    initSpinButton(diffuseRedSpinButton);
    initSpinButton(diffuseGreenSpinButton);
    initSpinButton(diffuseBlueSpinButton);
    diffuseRedSpinButton.signal_value_changed().connect( sigc::mem_fun(*this, &ModelViewerWindow::on_material_digits_changed) );
    diffuseGreenSpinButton.signal_value_changed().connect( sigc::mem_fun(*this, &ModelViewerWindow::on_material_digits_changed) );
    diffuseBlueSpinButton.signal_value_changed().connect( sigc::mem_fun(*this, &ModelViewerWindow::on_material_digits_changed) );
    
    materialAmbient.set_text("Ambient");
    materialAmbient.set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_START);
    materialAmbient.show();
    
    initSpinButton(ambientRedSpinButton);
    initSpinButton(ambientGreenSpinButton);
    initSpinButton(ambientBlueSpinButton);
    ambientRedSpinButton.signal_value_changed().connect( sigc::mem_fun(*this, &ModelViewerWindow::on_material_digits_changed) );
    ambientGreenSpinButton.signal_value_changed().connect( sigc::mem_fun(*this, &ModelViewerWindow::on_material_digits_changed) );
    ambientBlueSpinButton.signal_value_changed().connect( sigc::mem_fun(*this, &ModelViewerWindow::on_material_digits_changed) );

    materialSpecular.set_text("Specular");
    materialSpecular.set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_START);
    materialSpecular.show();
    
    initSpinButton(specularRedSpinButton);
    initSpinButton(specularGreenSpinButton);
    initSpinButton(specularBlueSpinButton);
    specularRedSpinButton.signal_value_changed().connect( sigc::mem_fun(*this, &ModelViewerWindow::on_material_digits_changed) );
    specularGreenSpinButton.signal_value_changed().connect( sigc::mem_fun(*this, &ModelViewerWindow::on_material_digits_changed) );
    specularBlueSpinButton.signal_value_changed().connect( sigc::mem_fun(*this, &ModelViewerWindow::on_material_digits_changed) );
    
    materialShininess.set_text("Shininess");
    materialShininess.set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_START);
    materialShininess.show();
    
    initSpinButton(shininessSpinButton);
    shininessSpinButton.signal_value_changed().connect( sigc::mem_fun(*this, &ModelViewerWindow::on_material_digits_changed) );
    
    objectContainer.add(materialDiffuse);
    objectContainer.add(diffuseRedSpinButton);
    objectContainer.add(diffuseGreenSpinButton);
    objectContainer.add(diffuseBlueSpinButton);
    
    objectContainer.add(materialAmbient);
    objectContainer.add(ambientRedSpinButton);
    objectContainer.add(ambientGreenSpinButton);
    objectContainer.add(ambientBlueSpinButton);
    
    objectContainer.add(materialSpecular);
    objectContainer.add(specularRedSpinButton);
    objectContainer.add(specularGreenSpinButton);
    objectContainer.add(specularBlueSpinButton);
    
    objectContainer.add(materialShininess);
    objectContainer.add(shininessSpinButton);
}

void ModelViewerWindow::initSpinButton(Gtk::SpinButton& button) {
    button.set_range(-1000.0, 1000.0);
    button.set_digits(2);
    button.set_increments(1.0, 0.0);
    button.show();
}

ModelViewerWindow::~ModelViewerWindow()
{
    
}

void ModelViewerWindow::on_flip_normals_clicked() {
    (*flipNormals) = true;
}

void ModelViewerWindow::on_smooth_movement_clicked() {
    std::cout << "The Button was clicked: state=" << (smoothMovement.get_active() ? "true" : "false") << std::endl;
    movement->isSmoothMovement = smoothMovement.get_active();
}

void ModelViewerWindow::on_light_position_digits_changed() {
    double x = lightXPositionSpinButton.get_value();
    double y = lightYPositionSpinButton.get_value();
    double z = lightZPositionSpinButton.get_value();
    lightProperties->position.x = x;
    lightProperties->position.y = y;
    lightProperties->position.z = z;
}

void ModelViewerWindow::on_light_color_digits_changed() {
    double r = lightRedColorSpinButton.get_value();
    double g = lightGreenColorSpinButton.get_value();
    double b = lightBlueColorSpinButton.get_value();
    lightProperties->intensity.r = r;
    lightProperties->intensity.g = g;
    lightProperties->intensity.b = b;
}

void ModelViewerWindow::on_material_digits_changed() {
    double dr = diffuseRedSpinButton.get_value();
    double dg = diffuseGreenSpinButton.get_value();
    double db = diffuseBlueSpinButton.get_value();
    
    double ar = ambientRedSpinButton.get_value();
    double ag = ambientGreenSpinButton.get_value();
    double ab = ambientBlueSpinButton.get_value();
    
    double sr = specularRedSpinButton.get_value();
    double sg = specularGreenSpinButton.get_value();
    double sb = specularBlueSpinButton.get_value();
    
    double s = shininessSpinButton.get_value();
    
    material->diffuse.r = dr;
    material->diffuse.g = dg;
    material->diffuse.b = db;
    material->ambient.r = ar;
    material->ambient.g = ag;
    material->ambient.b = ab;
    material->specular.r = sr;
    material->specular.g = sg;
    material->specular.b = sb;
    material->shininess = s;
}

void ModelViewerWindow::on_open_file_clicked() {
    // Open file
    (*fileName) = openFileEntry.get_text();
    (*shouldLoadFile) = true;
}



