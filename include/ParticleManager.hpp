//
// Created by edai on 17/04/18.
//

#ifndef SNOWSTORM_PARTICLEMANAGER_HPP
#define SNOWSTORM_PARTICLEMANAGER_HPP

#include <GL/gl.h>
#include <glm/vec4.hpp>
#include <glm/vec2.hpp>
#include <vector>
#include <random>
#include <SOIL/SOIL.h>

#define TEXTURES_NAME "snow1.png"
#define SNOW_SIZE 0.05f
#define MAX_PARTICLES 100000

struct Particle {
    glm::vec2 Position, Velocity;
    GLfloat Size;

    Particle() : Position(0.0f), Velocity(0.0f), Size(0.0f){
    }
    Particle(glm::vec2 p, glm::vec2 v, GLfloat l) : Position(p), Velocity(v), Size(l){
    }
};

class ParticleManager
{
public:
    void LoadTexture();
    void Render(float dt);

private:
    ParticleManager();
    ~ParticleManager() = default;
    void CreateRandomParticle(bool r = true);

    int spawnfactor;
    GLuint texture;
    std::vector<Particle> *buffer;
    std::random_device rd;

    #pragma SINGLETON
private:
    static ParticleManager* instance;

public:
    static ParticleManager* Instance()
    {
        if (instance == nullptr)
        {
            instance = new ParticleManager();
        }
        return instance;
    }
    #pragma

    void PutSnow(glm::vec2 &s, float size);

    void ResetPosition(Particle &p);
};

#endif //SNOWSTORM_PARTICLEMANAGER_HPP
