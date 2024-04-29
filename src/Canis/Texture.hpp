#pragma once

namespace Canis
{
    class Texture
    {
    public:
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

        void LoadTextures();
    };
}