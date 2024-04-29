#include <string>
#include <vector>
#include <iostream>
#include <SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Map.hpp"
#include "World.hpp"
#include "Model.hpp"
#include "Shader.hpp"

namespace Canis
{
    class Blocks
    {
    public:
        void BlocksInit(std::vector<std::vector<std::vector<unsigned int>>> _map, Canis::World world);
        Canis::GLTexture glassTexture;
        Canis::GLTexture grassTexture;
        Canis::GLTexture textureSpecular;
        Canis::GLTexture brickTexture;
        Canis::GLTexture stoneBrickTexture;
        Canis::GLTexture woodPlankTexture;
        Canis::GLTexture woodLogTexture;
        Canis::GLTexture dirtTexture;
        Canis::GLTexture grassBlockTopTexture;
        Canis::GLTexture grassUnwrappedTexture;
        Canis::GLTexture cobblestoneTexture;
        Canis::GLTexture poppyFlowerTexture;
        Canis::GLTexture chestOakTexture;
        Canis::GLTexture chestOakLeftTexture;
        Canis::GLTexture chestOakRightTexture;
        Canis::GLTexture fireTexture;

        /// Load Models
        Canis::Model cubeModel;
        Canis::Model grassModeL;
        Canis::Model cubeSideModel;
        Canis::Model fireModel;
        Canis::Model chestWholeModel;
        Canis::Model chestLeftModeL;
        Canis::Model chestRightModel;
        Canis::Model stairsModel;
        Canis::Model stairsOuterModel;
        /// END OF LOADING MODEL

        Canis::Shader shader;
        Canis::Shader grassShader;

    private:
    };
}