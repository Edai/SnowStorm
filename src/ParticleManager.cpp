//
// Created by edai on 17/04/18.
//

#include <iostream>
#include "ParticleManager.hpp"

ParticleManager *ParticleManager::instance = nullptr;

ParticleManager::ParticleManager()
{
    buffer = new std::vector<Particle>();
    spawnfactor = 10;
    for (int i = 0; i < spawnfactor; i++)
        CreateRandomParticle();
    for (auto &p : *buffer)
    {
        std::cout << "+++ " << p.Position.x << ", " << p.Position.y << std::endl;
        std::cout << "    " << p.Velocity.x << ", " << p.Velocity.y << std::endl;
    }
}

void ParticleManager::LoadTexture()
{
    texture = SOIL_load_OGL_texture(TEXTURES_NAME, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_ADD);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_ADD);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void ParticleManager::CreateRandomParticle()
{
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(-1.0, 1.0);
    static std::uniform_real_distribution<> dis_f(0.0, 0.15);

    auto *p = new Particle({dis(gen), 1.3}, {dis_f(gen), dis_f(gen)}, 1.0f);
    buffer->push_back(*p);
}

void ParticleManager::Render(float dt)
{
    for (auto p = buffer->begin(); p != buffer->end() ;)
    {
        p->Position += (p->Velocity * dt);
        p->Life  -= dt;
        if (p->Life < 0)
            buffer->erase(p);
        else
            p++;
    }
}
