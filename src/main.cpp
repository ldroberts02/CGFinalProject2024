#include <iostream>
#include <SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <math.h>
#include "Canis/Canis.hpp"
#include "Canis/Window.hpp"
#include "Canis/Shader.hpp"
#include "Canis/Debug.hpp"
#include "Canis/IOManager.hpp"
#include "Canis/InputManager.hpp"
#include "Canis/Camera.hpp"
#include "Canis/Editor.hpp"
#include "Canis/Model.hpp"
#include "Canis/World.hpp"
#include "Canis/FrameRateManager.hpp"

using namespace glm;

// map init, a 3d array that stores a lot of numbers to "simulate" 3d coordinates by stacking numbers in order, to offset models that are spawned
std::vector<std::vector<std::vector<unsigned int>>> map = {};

// declare functions here

void SpawnLights(Canis::World &_world);
void LoadMap(std::string _path);

int randomNum;

int main(int argc, char *argv[])
{
    srand(time(NULL)); // Sets random seed
    Canis::Init();
    Canis::InputManager inputManager;
    Canis::FrameRateManager frameRateManager;
    frameRateManager.Init(60);

    /// SETUP WINDOW
    Canis::Window window;
    window.MouseLock(true);

    unsigned int flags = 0;

    if (Canis::GetConfig().fullscreen)
        flags |= Canis::WindowFlags::FULLSCREEN;

    window.Create("Computer Graphics Spring 2024 Final", Canis::GetConfig().width, Canis::GetConfig().heigth, flags);
    /// END OF WINDOW SETUP

    Canis::World world(&window, &inputManager, "assets/textures/lowpoly-skybox/");

    Canis::Editor editor(&window, &world);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_ALPHA);

    // Load Map into 3d array and process it

    LoadMap("assets/maps/level.map");

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

    /// START OF IMAGE LOADING
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
    Canis::GLTexture orchidFlowerTexture = Canis::LoadImageGL("assets/textures/blue_orchid.png", false);
    Canis::GLTexture chestOakTexture = Canis::LoadImageGL("assets/textures/chest_oak.png", true);
    Canis::GLTexture chestOakLeftTexture = Canis::LoadImageGL("assets/textures/chest_oak_left.png", false);
    Canis::GLTexture chestOakRightTexture = Canis::LoadImageGL("assets/textures/chest_oak_right.png", false);
    Canis::GLTexture fireTexture = Canis::LoadImageGL("assets/textures/fire/fire_1.png", true);
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

    /// START OF BLOCK INITIALIZATION
    for (int y = 0; y < map.size(); y++)
    {
        for (int x = 0; x < map[y].size(); x++)
        {
            for (int z = 0; z < map[y][x].size(); z++)
            {
                Canis::Entity entity;
                entity.active = true;

                randomNum = rand() % 7; // sets randomNum to random number between 0 and 7
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
                    // skipping case 2 so i dont have to rewrite all numbers in map file

                case 3: // check for flower or grass, uses randomNum to place
                    switch (randomNum)
                    {
                    case 0: // swaying grass
                        entity.tag = "grass";
                        entity.albedo = &grassTexture;
                        entity.specular = &textureSpecular;
                        entity.model = &grassModel;
                        entity.shader = &grassShader;
                        entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                        world.Spawn(entity);
                        break;
                    case 4: // orchid flower
                        entity.tag = "flower";
                        entity.albedo = &orchidFlowerTexture;
                        entity.specular = &textureSpecular;
                        entity.model = &grassModel;
                        entity.shader = &grassShader;
                        entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                        world.Spawn(entity);
                        break;
                    case 6: // poppy flower
                        entity.tag = "flower";
                        entity.albedo = &poppyFlowerTexture;
                        entity.specular = &textureSpecular;
                        entity.model = &grassModel;
                        entity.shader = &grassShader;
                        entity.transform.position = vec3(x + 0.0f, y + 0.0f, z + 0.0f);
                        world.Spawn(entity);
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
    /// END OF BLOCK INITIALIZATION

    std::vector<Canis::Entity *> fire = world.GetEntitiesWithTag("fire"); // calling the fire entity

    SpawnLights(world); // Init Lights

    double deltaTime = 0.0;
    double fps = 0.0;
    double timeSeconds = 0.0;

    Canis::PointLight *TestLight = world.GetPointLight(vec3(7.0f, 3.0f, 10.0f)); // get light in position

    // Application loop
    while (inputManager.Update(Canis::GetConfig().width, Canis::GetConfig().heigth))
    {
        deltaTime = frameRateManager.StartFrame();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        timeSeconds += deltaTime;                    // will give the time in seconds
        if (int(fmod((timeSeconds * 100), 10)) != 5) // if the value of the tenths place of timeSeconds is not modulous of 5, then
        {
            TestLight->ambient = vec3(0.5f, 0.1f, 0.0f); // set light color to redish orange
        }
        else
        {
            TestLight->ambient = vec3(0.0f, 0.0f, 0.0f); // set light color to none (off)
        }

        for (Canis::Entity *f : fire)
        {
            f->albedo = &fireTextureList[int(fmod(timeSeconds * 20, 31))]; //update fire texture with next picture in list, 20 times a second
        }

        world.Update(deltaTime);
        world.Draw(deltaTime);

        editor.Draw();

        window.SwapBuffer();

        // EndFrame will pause the app when running faster than frame limit
        fps = frameRateManager.EndFrame();
    }

    return 0;
}
void LoadMap(std::string _path)
{
    {

        std::ifstream file;
        file.open(_path);

        if (!file.is_open())
        {
            printf("file not found at: %s \n", _path.c_str());
            exit(1);
        }

        int number = 0;
        int layer = 0;

        map.push_back(std::vector<std::vector<unsigned int>>());
        map[layer].push_back(std::vector<unsigned int>());

        while (file >> number)
        {
            if (number == -2) // add new layer
            {
                layer++;
                map.push_back(std::vector<std::vector<unsigned int>>());
                map[map.size() - 1].push_back(std::vector<unsigned int>());
                continue;
            }

            if (number == -1) // add new row
            {
                map[map.size() - 1].push_back(std::vector<unsigned int>());
                continue;
            }

            map[map.size() - 1][map[map.size() - 1].size() - 1].push_back((unsigned int)number);
        }
    }
}
void SpawnLights(Canis::World &_world)
{
    Canis::DirectionalLight directionalLight;
    _world.SpawnDirectionalLight(directionalLight);

    Canis::PointLight pointLight;

    pointLight.position = vec3(7.0f, 25.0f, 10.0f);
    pointLight.ambient = vec3(0.8f);
    pointLight.diffuse = vec3(0.5f);
    pointLight.specular = vec3(1.0f);
    pointLight.constant = 1.0f;
    pointLight.linear = 0.09f;
    pointLight.quadratic = 0.0f;

    _world.SpawnPointLight(pointLight);

    pointLight.position = vec3(7.0f, -15.0f, 10.0f);
    pointLight.ambient = vec3(0.2f, 0.2f, 0.2f);

    _world.SpawnPointLight(pointLight);

    pointLight.position = vec3(-2.0f);
    pointLight.ambient = vec3(0.2f, 0.2f, 0.2f);

    _world.SpawnPointLight(pointLight);

    // Controlled Light
    pointLight.position = vec3(7.0f, 3.0f, 10.0f);
    pointLight.ambient = vec3(0.0f, 0.0f, 0.0f);
    pointLight.linear = 1.4f;
    pointLight.constant = 0.8f;
    pointLight.quadratic = 0.1f;

    _world.SpawnPointLight(pointLight);
}
