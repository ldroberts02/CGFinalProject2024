#include "Blocks.hpp"
#include <iostream>
#include <vector>
#include <SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include "Canis.hpp"
#include "Entity.hpp"
#include "Debug.hpp"
// #include "Map.hpp"
#include "Texture.hpp"
#include "World.hpp"
#include "IOManager.hpp"
#include "Model.hpp"
#include "Shader.hpp"

#pragma once

using namespace glm;

namespace Canis
{
    void Blocks::BlocksInit(std::vector<std::vector<std::vector<unsigned int>>> map, Canis::World world)
    {
    /// SETUP SHADER

    Canis::Shader shader;
    Canis::Shader grassShader;

    shader.Compile("assets/shaders/hello_shader.vs", "assets/shaders/hello_shader.fs");
    shader.AddAttribute("aPosition");
    shader.Link();
    shader.Use();
    shader.SetInt("MATERIAL.diffuse", 0);
    shader.SetInt("MATERIAL.specular", 1);
    shader.SetFloat("MATERIAL.shininess", 64);
    shader.SetBool("WIND", false);
    shader.UnUse();

    grassShader.Compile("assets/shaders/hello_shader.vs", "assets/shaders/hello_shader.fs");
    grassShader.AddAttribute("aPosition");
    grassShader.Link();
    grassShader.Use();
    grassShader.SetInt("MATERIAL.diffuse", 0);
    grassShader.SetInt("MATERIAL.specular", 1);
    grassShader.SetFloat("MATERIAL.shininess", 64);
    grassShader.SetBool("WIND", true);
    grassShader.SetFloat("WINDEFFECT", 0.2);
    grassShader.UnUse();
    /// END OF SHADER

    Canis::GLTexture glassTexture = Canis::LoadImageGL("assets/textures/glass.png", true);
    Canis::GLTexture grassTexture = Canis::LoadImageGL("assets/textures/grass.png", false);
    Canis::GLTexture textureSpecular = Canis::LoadImageGL("assets/textures/black.png", true);
    Canis::GLTexture brickTexture = Canis::LoadImageGL("assets/textures/bricks.png", true);
    Canis::GLTexture stoneBrickTexture = Canis::LoadImageGL("assets/textures/stone_bricks.png", true);
    Canis::GLTexture woodPlankTexture = Canis::LoadImageGL("assets/textures/oak_planks.png", true);
    Canis::GLTexture woodLogTexture = Canis::LoadImageGL("assets/textures/oak_log.png", true);
    Canis::GLTexture dirtTexture = Canis::LoadImageGL("assets/textures/dirt.png", true);
    Canis::GLTexture grassBlockTopTexture = Canis::LoadImageGL("assets/textures/grass_block_top.png", true);
    Canis::GLTexture grassUnwrappedTexture = Canis::LoadImageGL("assets/textures/grass_unwrapped.png", false);
    Canis::GLTexture cobblestoneTexture = Canis::LoadImageGL("assets/textures/cobblestone.png", true);
    Canis::GLTexture poppyFlowerTexture = Canis::LoadImageGL("assets/textures/poppy.png", false);
    Canis::GLTexture chestOakTexture = Canis::LoadImageGL("assets/textures/chest_oak.png", true);
    Canis::GLTexture chestOakLeftTexture = Canis::LoadImageGL("assets/textures/chest_oak_left.png", false);
    Canis::GLTexture chestOakRightTexture = Canis::LoadImageGL("assets/textures/chest_oak_right.png", false);
    Canis::GLTexture fireTexture = Canis::LoadImageGL("assets/textures/ForcePush.png", true);
    /// End of Image Loading

    /// Start of Fire Texture List

    Canis::GLTexture fireTextureList[31] = {
        Canis::LoadImageGL("assets/textures/fire/fire_1.png", true),
        Canis::LoadImageGL("assets/textures/fire/fire_2.png", true),
        Canis::LoadImageGL("assets/textures/fire/fire_3.png", true),
        Canis::LoadImageGL("assets/textures/fire/fire_4.png", true),
        Canis::LoadImageGL("assets/textures/fire/fire_5.png", true),
        Canis::LoadImageGL("assets/textures/fire/fire_6.png", true),
        Canis::LoadImageGL("assets/textures/fire/fire_7.png", true),
        Canis::LoadImageGL("assets/textures/fire/fire_8.png", true),
        Canis::LoadImageGL("assets/textures/fire/fire_9.png", true),
        Canis::LoadImageGL("assets/textures/fire/fire_10.png", true),
        Canis::LoadImageGL("assets/textures/fire/fire_11.png", true),
        Canis::LoadImageGL("assets/textures/fire/fire_12.png", true),
        Canis::LoadImageGL("assets/textures/fire/fire_13.png", true),
        Canis::LoadImageGL("assets/textures/fire/fire_14.png", true),
        Canis::LoadImageGL("assets/textures/fire/fire_15.png", true),
        Canis::LoadImageGL("assets/textures/fire/fire_16.png", true),
        Canis::LoadImageGL("assets/textures/fire/fire_17.png", true),
        Canis::LoadImageGL("assets/textures/fire/fire_18.png", true),
        Canis::LoadImageGL("assets/textures/fire/fire_19.png", true),
        Canis::LoadImageGL("assets/textures/fire/fire_20.png", true),
        Canis::LoadImageGL("assets/textures/fire/fire_21.png", true),
        Canis::LoadImageGL("assets/textures/fire/fire_22.png", true),
        Canis::LoadImageGL("assets/textures/fire/fire_23.png", true),
        Canis::LoadImageGL("assets/textures/fire/fire_24.png", true),
        Canis::LoadImageGL("assets/textures/fire/fire_25.png", true),
        Canis::LoadImageGL("assets/textures/fire/fire_26.png", true),
        Canis::LoadImageGL("assets/textures/fire/fire_27.png", true),
        Canis::LoadImageGL("assets/textures/fire/fire_28.png", true),
        Canis::LoadImageGL("assets/textures/fire/fire_29.png", true),
        Canis::LoadImageGL("assets/textures/fire/fire_30.png", true),
        Canis::LoadImageGL("assets/textures/fire/fire_31.png", true)};

    /// End of Fire Texture List

    /// Load Models
    Canis::Model cubeModel = Canis::LoadModel("assets/models/cube.obj");
    Canis::Model grassModel = Canis::LoadModel("assets/models/plants.obj");
    Canis::Model cubeSideModel = Canis::LoadModel("assets/models/cubeUnwrapped.obj");
    Canis::Model fireModel = Canis::LoadModel("assets/models/fire_model_clipped.obj");
    Canis::Model chestWholeModel = Canis::LoadModel("assets/models/chest.obj");
    Canis::Model chestLeftModel = Canis::LoadModel("assets/models/chest_left.obj");
    Canis::Model chestRightModel = Canis::LoadModel("assets/models/chest_right.obj");
    Canis::Model stairsModel = Canis::LoadModel("assets/models/stairs.obj");
    Canis::Model stairsOuterModel = Canis::LoadModel("assets/models/stairs_outer.obj");
    /// END OF LOADING MODEL

    int randomNum;
    srand(1); // set to srand(1) for a solid repeating number, or srand(time(NULL)) for whatever it will give on launch (pseudo random)
    for (int y = 0; y < map.size(); y++)
    {
        for (int x = 0; x < map[y].size(); x++)
        {
            for (int z = 0; z < map[y][x].size(); z++)
            {
                Canis::Entity entity;
                entity.active = true;

                randomNum = rand() % 5;
                // Canis::Log(std::to_string(randomNum));
                switch (map[y][x][z])
                {
                case 1: // places a glass block
                    entity.tag = "glass";
                    entity.albedo = &glassTexture;
                    entity.specular = &textureSpecular;
                    entity.model = &cubeModel;
                    entity.shader = &shader;
                    entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                    world.Spawn(entity);
                    break;
                case 2: // places a moving grass block
                    entity.tag = "grass";
                    entity.albedo = &grassTexture;
                    entity.specular = &textureSpecular;
                    entity.model = &grassModel;
                    entity.shader = &grassShader;
                    entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                    world.Spawn(entity);
                    break;
                case 3: // check for flower slash grass
                    switch (randomNum)
                    {
                    case 0:
                        break;
                    case 1:
                        entity.tag = "grass";
                        entity.albedo = &grassTexture;
                        entity.specular = &textureSpecular;
                        entity.model = &grassModel;
                        entity.shader = &grassShader;
                        entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                        world.Spawn(entity);
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                    case 4:
                        entity.tag = "flower";
                        entity.albedo = &poppyFlowerTexture;
                        entity.specular = &textureSpecular;
                        entity.model = &grassModel;
                        entity.shader = &grassShader;
                        entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                        world.Spawn(entity);
                        break;
                    case 5:
                        break;
                    default:
                        break;
                    }
                    break;
                case 4: // places a woodPlank block
                    entity.tag = "woodenPlank";
                    entity.albedo = &woodPlankTexture;
                    entity.specular = &textureSpecular;
                    entity.model = &cubeModel;
                    entity.shader = &shader;
                    entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                    world.Spawn(entity);
                    break;
                case 5: // places a woodLog block
                    entity.tag = "woodLog";
                    entity.albedo = &woodLogTexture;
                    entity.specular = &textureSpecular;
                    entity.model = &cubeModel;
                    entity.shader = &shader;
                    entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                    world.Spawn(entity);
                    break;
                case 6: // places a brick block
                    entity.tag = "brick";
                    entity.albedo = &brickTexture;
                    entity.specular = &textureSpecular;
                    entity.model = &cubeModel;
                    entity.shader = &shader;
                    entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                    world.Spawn(entity);
                    break;
                case 7: // places a dirt block
                    entity.tag = "dirt";
                    entity.albedo = &dirtTexture;
                    entity.specular = &textureSpecular;
                    entity.model = &cubeModel;
                    entity.shader = &shader;
                    entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                    world.Spawn(entity);
                    break;
                case 8: // places a grass block
                    entity.tag = "grass";
                    entity.albedo = &grassUnwrappedTexture;
                    entity.specular = &textureSpecular;
                    entity.model = &cubeSideModel;
                    entity.shader = &shader;
                    entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                    world.Spawn(entity);
                    break;
                case 9: // places a cobblestone block
                    entity.tag = "cobblestone";
                    entity.albedo = &cobblestoneTexture;
                    entity.specular = &textureSpecular;
                    entity.model = &cubeModel;
                    entity.shader = &shader;
                    entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                    world.Spawn(entity);
                    break;
                case 10: // places a fire block
                    entity.tag = "fire";
                    entity.albedo = &fireTexture;
                    entity.specular = &textureSpecular;
                    entity.model = &fireModel;
                    entity.shader = &shader;
                    entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                    world.Spawn(entity);
                    break;
                case 11: // places a fire block
                    entity.tag = "chestwhole";
                    entity.albedo = &chestOakTexture;
                    entity.specular = &textureSpecular;
                    entity.model = &chestWholeModel;
                    entity.shader = &shader;
                    entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                    world.Spawn(entity);
                    break;
                case 12: // places a left long chest block
                    entity.tag = "chestleft";
                    entity.albedo = &chestOakLeftTexture;
                    entity.specular = &textureSpecular;
                    entity.model = &chestLeftModel;
                    entity.shader = &shader;
                    entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                    world.Spawn(entity);
                    break;
                case 13: // places a right long chest block
                    entity.tag = "chestright";
                    entity.albedo = &chestOakRightTexture;
                    entity.specular = &textureSpecular;
                    entity.model = &chestRightModel;
                    entity.shader = &shader;
                    entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                    world.Spawn(entity);
                    break;
                case 14: // places a stair block
                    entity.tag = "stair_cobble";
                    entity.albedo = &cobblestoneTexture;
                    entity.specular = &textureSpecular;
                    entity.model = &stairsModel;
                    entity.shader = &shader;
                    entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                    world.Spawn(entity);
                    break;
                case 15: // places a stair block facing the opposite direction
                    entity.tag = "stair_cobble";
                    entity.albedo = &cobblestoneTexture;
                    entity.specular = &textureSpecular;
                    entity.model = &stairsModel;
                    entity.shader = &shader;
                    entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                    entity.transform.rotation = vec3(0.0f, radians(180.0f), 0.0f); // degrees are in radians, so conversions are needed
                    world.Spawn(entity);
                    break;
                case 16: // places a stair block facing
                    entity.tag = "stair_brick";
                    entity.albedo = &stoneBrickTexture;
                    entity.specular = &textureSpecular;
                    entity.model = &stairsModel;
                    entity.shader = &shader;
                    entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                    world.Spawn(entity);
                    break;
                case 17: // places a stair block facing
                    entity.tag = "stair_brick";
                    entity.albedo = &stoneBrickTexture;
                    entity.specular = &textureSpecular;
                    entity.model = &stairsModel;
                    entity.shader = &shader;
                    entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                    entity.transform.rotation = vec3(0.0f, radians(90.0f), 0.0f);
                    world.Spawn(entity);
                    break;
                case 18: // places a stair block facing
                    entity.tag = "stair_brick";
                    entity.albedo = &stoneBrickTexture;
                    entity.specular = &textureSpecular;
                    entity.model = &stairsModel;
                    entity.shader = &shader;
                    entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                    entity.transform.rotation = vec3(0.0f, radians(180.0f), 0.0f);
                    world.Spawn(entity);
                    break;
                case 19: // places a stair block facing
                    entity.tag = "stair_brick";
                    entity.albedo = &stoneBrickTexture;
                    entity.specular = &textureSpecular;
                    entity.model = &stairsModel;
                    entity.shader = &shader;
                    entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                    entity.transform.rotation = vec3(0.0f, radians(270.0f), 0.0f);
                    world.Spawn(entity);
                    break;
                case 20: // places a outer stair block facing
                    entity.tag = "stair_brick";
                    entity.albedo = &stoneBrickTexture;
                    entity.specular = &textureSpecular;
                    entity.model = &stairsOuterModel;
                    entity.shader = &shader;
                    entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                    world.Spawn(entity);
                    break;
                case 21: // places a outer stair block facing
                    entity.tag = "stair_brick";
                    entity.albedo = &stoneBrickTexture;
                    entity.specular = &textureSpecular;
                    entity.model = &stairsOuterModel;
                    entity.shader = &shader;
                    entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                    entity.transform.rotation = vec3(0.0f, radians(90.0f), 0.0f);
                    world.Spawn(entity);
                    break;
                case 22: // places a outer stair block facing
                    entity.tag = "stair_brick";
                    entity.albedo = &stoneBrickTexture;
                    entity.specular = &textureSpecular;
                    entity.model = &stairsOuterModel;
                    entity.shader = &shader;
                    entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                    entity.transform.rotation = vec3(0.0f, radians(180.0f), 0.0f);
                    world.Spawn(entity);
                    break;
                case 23: // places a outer stair block facing
                    entity.tag = "stair_brick";
                    entity.albedo = &stoneBrickTexture;
                    entity.specular = &textureSpecular;
                    entity.model = &stairsOuterModel;
                    entity.shader = &shader;
                    entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                    entity.transform.rotation = vec3(0.0f, radians(270.0f), 0.0f);
                    world.Spawn(entity);
                    break;
                case 24: // places a stair block facing
                    entity.tag = "stair_wood";
                    entity.albedo = &woodPlankTexture;
                    entity.specular = &textureSpecular;
                    entity.model = &stairsModel;
                    entity.shader = &shader;
                    entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                    world.Spawn(entity);
                    break;
                case 25: // places a stair block facing
                    entity.tag = "stair_wood";
                    entity.albedo = &woodPlankTexture;
                    entity.specular = &textureSpecular;
                    entity.model = &stairsModel;
                    entity.shader = &shader;
                    entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                    entity.transform.rotation = vec3(0.0f, radians(90.0f), 0.0f);
                    world.Spawn(entity);
                    break;
                case 26: // places a stair block facing
                    entity.tag = "stair_wood";
                    entity.albedo = &woodPlankTexture;
                    entity.specular = &textureSpecular;
                    entity.model = &stairsModel;
                    entity.shader = &shader;
                    entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                    entity.transform.rotation = vec3(0.0f, radians(180.0f), 0.0f);
                    world.Spawn(entity);
                    break;
                case 27: // places a stair block facing
                    entity.tag = "stair_wood";
                    entity.albedo = &woodPlankTexture;
                    entity.specular = &textureSpecular;
                    entity.model = &stairsModel;
                    entity.shader = &shader;
                    entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                    entity.transform.rotation = vec3(0.0f, radians(270.0f), 0.0f);
                    world.Spawn(entity);
                    break;
                case 28: // places a outer stair block facing
                    entity.tag = "stair_wood";
                    entity.albedo = &woodPlankTexture;
                    entity.specular = &textureSpecular;
                    entity.model = &stairsOuterModel;
                    entity.shader = &shader;
                    entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                    world.Spawn(entity);
                    break;
                case 29: // places a outer stair block facing
                    entity.tag = "stair_wood";
                    entity.albedo = &woodPlankTexture;
                    entity.specular = &textureSpecular;
                    entity.model = &stairsOuterModel;
                    entity.shader = &shader;
                    entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                    entity.transform.rotation = vec3(0.0f, radians(90.0f), 0.0f);
                    world.Spawn(entity);
                    break;
                case 30: // places a outer stair block facing
                    entity.tag = "stair_wood";
                    entity.albedo = &woodPlankTexture;
                    entity.specular = &textureSpecular;
                    entity.model = &stairsOuterModel;
                    entity.shader = &shader;
                    entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                    entity.transform.rotation = vec3(0.0f, radians(180.0f), 0.0f);
                    world.Spawn(entity);
                    break;
                case 31: // places a outer stair block facing
                    entity.tag = "stair_wood";
                    entity.albedo = &woodPlankTexture;
                    entity.specular = &textureSpecular;
                    entity.model = &stairsOuterModel;
                    entity.shader = &shader;
                    entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                    entity.transform.rotation = vec3(0.0f, radians(270.0f), 0.0f);
                    world.Spawn(entity);
                    break;
                default:
                    break;
                }
            }
        }
    }
       
    }
}