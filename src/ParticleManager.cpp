//
// Created by edai on 17/04/18.
//

#include <iostream>
#include "ParticleManager.hpp"

ParticleManager *ParticleManager::instance = nullptr;

ParticleManager::ParticleManager()
{
    buffer = new std::vector<Particle>();
    spawnfactor = 100;
    for (int i = 0; i < spawnfactor; i++)
        CreateRandomParticle();
}

void ParticleManager::LoadTexture()
{
    texture = SOIL_load_OGL_texture(TEXTURES_NAME, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_ADD);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_ADD);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void ParticleManager::CreateRandomParticle()
{
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(-1.0, 1.0);
    static std::uniform_real_distribution<> dis_f(0.0, 0.05);

    auto *p = new Particle({dis(gen), dis(gen)}, {0.0, - dis_f(gen)}, 10.0f);
    buffer->push_back(*p);
}

void ParticleManager::PutSnow(glm::vec2 &s)
{
    float size = 0.05f;

    std::cout << s.x << " " << s.y << std::endl;
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glTexCoord2i(0, 1);
    glVertex2f(s.x - size, s.y + size);
    glTexCoord2i(1, 1);
    glVertex2f(s.x + size, s.y + size);
    glTexCoord2i(1, 0);
    glVertex2f(s.x + size, s.y - size);
    glTexCoord2i(0, 0);
    glVertex2f(s.x - size, s.y - size);
}

void ParticleManager::Render(float dt)
{
    glBegin(GL_QUADS);
    for (auto p = buffer->begin(); p != buffer->end() ;)
    {
        PutSnow(p->Position);
        p->Position += (p->Velocity * dt);
        p->Life  -= dt;
        if (p->Position.y < -1.0f)
            buffer->erase(p);
        else
            p++;
    }
    glEnd();
}
