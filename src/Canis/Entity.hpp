#pragma once
#include <string>
#include "Model.hpp"
#include "Shader.hpp"
#include "Data/Transform.hpp"
#include "Data/GLTexture.hpp"

namespace Canis
{
    class World;

    struct Entity
    {
        bool active = true;
        std::string name;
        std::string tag;
        Transform transform;
        Model *model;
        Shader *shader;
        GLTexture *albedo;
        GLTexture *specular;
        void (*Update)(World &_world, Entity &_entity, float _deltaTime) = nullptr;
    };
}