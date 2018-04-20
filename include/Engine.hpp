//
// Created by edai on 20/03/18.
//

#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "GraphicalCore.hpp"
#include "ParticleManager.hpp"

#include <glm/glm.hpp>
#include <list>
#include <array>
#include <vector>

class Engine
{
public:
    Engine();
    ~Engine();
    void Update(float dt);

    enum SKYBOX_ORIENTATION {
        NEGATIVE_X, //bk
        POSITIVE_X, //lf
        NEGATIVE_Y, //dn
        POSITIVE_Y, //up
        NEGATIVE_Z, //rt
        POSITIVE_Z //ft
    };

private:
    void InitLights();
    GLuint skybox[6];

#pragma SINGLETON
private:
    static Engine* instance;

public:
    static Engine* Instance()
    {
        if (instance == nullptr)
        {
            instance = new Engine();
        }
        return instance;
    }

#pragma END SINGLETON

    void InitSkybox();
    void DisplaySkybox();
};

#endif //ENGINE_HPP
