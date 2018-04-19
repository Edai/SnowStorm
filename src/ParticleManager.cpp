//
// Created by edai on 17/04/18.
//

#include <iostream>
#include "ParticleManager.hpp"
#include <algorithm>

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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void ParticleManager::CreateRandomParticle(bool random)
{
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(-1.0f, 1.0f);
    static std::uniform_real_distribution<> dis_f(0.05f, 0.15f);
    static std::uniform_real_distribution<> dis_s(SNOW_SIZE  - 0.025f, SNOW_SIZE + 0.05f);

    auto *p = new Particle({dis(gen), random ? dis(gen) : 1.0f + SNOW_SIZE}, {0.0, - dis_f(gen)}, (float)dis_s(gen));
    buffer->push_back(*p);
}

void ParticleManager::PutSnow(glm::vec2 &s, float size)
{
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
    static float timer = 0.0f;

    timer += dt;
    if (timer > 0.01f && spawnfactor < MAX_PARTICLES)
    {
        CreateRandomParticle(false);
        spawnfactor++;
        timer = 0.0f;
    }
    glBegin(GL_QUADS);
    for (auto p = buffer->begin(); p != buffer->end() ; )
    {
        PutSnow(p->Position, p->Size);
        p->Position += (p->Velocity * dt);
        if (p->Position.y < -1.0f - SNOW_SIZE)
        {
            buffer->erase(p);
            spawnfactor--;
        }
        else
            p++;
    }
    std::cout << spawnfactor << std::endl;
    glEnd();
    glPopMatrix();
}
