//
// Created by edai on 20/03/18.
//

#include <sstream>
#include <random>
#include "Engine.hpp"

Engine *Engine::instance = nullptr;

Engine::~Engine() = default;

void Engine::InitLights()
{
    GLfloat light_ambient[] = {0.10, 0.1, 0.10, 1.0};
    GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_position[] = {0.0, 0.0, -10.0f, 1.0};
    GLfloat mat_diffuse[] = {0.9, 0.9, 0.9, 1.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {120.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
}

void Engine::InitTextures()
{
    std::vector<std::string> *names = new std::vector<std::string>({TEXTURES_NAMES});
    textures = new std::vector<GLuint>();
    for (auto &s : *names)
        textures->push_back(SOIL_load_OGL_texture(s.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA));
    glBindTexture(GL_TEXTURE_2D, (*textures)[0]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_ADD);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_ADD);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

Engine::Engine()
{
    InitTextures();
    InitLights();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_COLOR_MATERIAL);
}

void Engine::InitUpdate()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D);
    glLoadIdentity();
}

void Engine::EndUpdate()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glDisable(GL_TEXTURE_2D);
}

void Engine::Update()
{
    glLoadIdentity();
}
