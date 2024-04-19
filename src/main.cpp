#include <iostream>
#include <SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include "Canis/Canis.hpp"
#include "Canis/Window.hpp"
#include "Canis/Shader.hpp"
#include "Canis/Debug.hpp"
#include "Canis/IOManager.hpp"
#include "Canis/InputManager.hpp"
#include "Canis/Camera.hpp"
#include "Canis/Model.hpp"

using namespace glm;

// git restore .
// git fetch
// git pull

struct PointLight {
    vec3 position;  
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	
    float constant;
    float linear;
    float quadratic;
};

// set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };

// world space positions of our cubes
glm::vec3 cubePositions[] = {
    glm::vec3(0.0f, 0.0f, 2.0f),
    glm::vec3(2.0f, 5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f, 3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f, 2.0f, -2.5f),
    glm::vec3(1.5f, 0.2f, -1.5f),
    glm::vec3(-1.3f, 1.0f, -1.5f)};

std::vector<PointLight> pointLights = {};

void UpdatePointLight(Canis::Shader &_shader, PointLight &_pointLight, int _index)
{
    _shader.SetVec3("POINTLIGHTS[" + std::to_string(_index) + "].position", _pointLight.position);
    _shader.SetVec3("POINTLIGHTS[" + std::to_string(_index) + "].ambient", _pointLight.ambient);
    _shader.SetVec3("POINTLIGHTS[" + std::to_string(_index) + "].diffuse", _pointLight.diffuse);
    _shader.SetVec3("POINTLIGHTS[" + std::to_string(_index) + "].specular", _pointLight.specular);
    _shader.SetFloat("POINTLIGHTS[" + std::to_string(_index) + "].constant", _pointLight.constant);
    _shader.SetFloat("POINTLIGHTS[" + std::to_string(_index) + "].linear", _pointLight.linear);
    _shader.SetFloat("POINTLIGHTS[" + std::to_string(_index) + "].quadratic", _pointLight.quadratic);
}

void UpdateCameraMovement(Canis::InputManager &_inputManager, Canis::Window &_window, Canis::Camera &_camera)
{
    if (_inputManager.GetKey(SDL_SCANCODE_W))
        _camera.ProcessKeyboard(Canis::Camera_Movement::FORWARD, 0.0016f);

    if (_inputManager.GetKey(SDL_SCANCODE_S))
        _camera.ProcessKeyboard(Canis::Camera_Movement::BACKWARD, 0.0016f);
    
    if (_inputManager.GetKey(SDL_SCANCODE_A))
        _camera.ProcessKeyboard(Canis::Camera_Movement::LEFT, 0.0016f);
    
    if (_inputManager.GetKey(SDL_SCANCODE_D))
        _camera.ProcessKeyboard(Canis::Camera_Movement::RIGHT, 0.0016f);

    if (_window.GetMouseLock())
        _camera.ProcessMouseMovement(_inputManager.mouseRel.x, -_inputManager.mouseRel.y, true);

    if (_inputManager.JustPressedKey(SDLK_ESCAPE))
        _window.MouseLock(!_window.GetMouseLock());
}

int main(int argc, char *argv[])
{
    Canis::Init();
    Canis::InputManager inputManager;
    Canis::Camera camera(vec3(0.0f, 0.0f, -3.0f));

    /// SETUP WINDOW
    Canis::Window window;
    window.MouseLock(true);

    unsigned int flags = 0;

    if (Canis::GetProjectConfig().fullscreen)
        flags |= Canis::WindowFlags::FULLSCREEN;

    window.Create("Hello Graphics",
                  Canis::GetProjectConfig().width,
                  Canis::GetProjectConfig().heigth,
                  flags);
    /// END OF WINDOW SETUP



    PointLight pointLight;
    pointLight.position = vec3(0.0f);
    pointLight.ambient = vec3(0.2f);
    pointLight.diffuse = vec3(0.5f);
    pointLight.specular = vec3(1.0f);
    pointLight.constant = 1.0f;
    pointLight.linear = 0.09f;
    pointLight.quadratic = 0.032f;

    pointLights.push_back(pointLight);

    pointLight.position = vec3(0.0f, 0.0f, 1.0f);
    pointLight.ambient = vec3(4.0f, 0.0f, 0.0f);

    pointLights.push_back(pointLight);

    pointLight.position = vec3(-2.0f);
    pointLight.ambient = vec3(0.0f, 4.0f, 0.0f);

    pointLights.push_back(pointLight);

    pointLight.position = vec3(2.0f);
    pointLight.ambient = vec3(0.0f, 0.0f, 4.0f);

    pointLights.push_back(pointLight);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_ALPHA);

    /// SETUP SHADER
    Canis::Shader shader;
    shader.Compile("assets/shaders/hello_shader.vs", "assets/shaders/hello_shader.fs");
    shader.AddAttribute("aPosition");
    shader.Link();
    /// END OF SHADER

    /// Load Image
    Canis::GLTexture texture = Canis::LoadImageGL("assets/textures/glass.png");
    Canis::GLTexture grassTexture = Canis::LoadImageGL("assets/textures/grass.png");
    Canis::GLTexture textureSpecular = Canis::LoadImageGL("assets/textures/container2_specular.png");
    /// End of Image Loading

    /// Load Models
    Canis::Model cubeModel = Canis::LoadModel("assets/models/cube.obj");
    Canis::Model grassModel = Canis::LoadModel("assets/models/plants.obj");
    /// END OF LOADING MODEL

    unsigned int lastTime = SDL_GetTicks();

    while (inputManager.Update(Canis::GetProjectConfig().width, Canis::GetProjectConfig().heigth))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        UpdateCameraMovement(inputManager, window, camera);

        shader.Use();
        shader.SetVec3("COLOR", 0.0f, 0.0f, 1.0f);
        shader.SetVec3("VIEWPOS", camera.Position);

        shader.SetInt("NUMBEROFPOINTLIGHTS", 4);

        shader.SetFloat("TIME", SDL_GetTicks()/1000.0f);

        UpdatePointLight(shader, pointLights[0], 0);
        UpdatePointLight(shader, pointLights[1], 1);
        UpdatePointLight(shader, pointLights[2], 2);
        UpdatePointLight(shader, pointLights[3], 3);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.id);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textureSpecular.id);

        shader.SetInt("MATERIAL.diffuse", 0);
        shader.SetInt("MATERIAL.specular", 1);
        shader.SetFloat("MATERIAL.shininess", 64);

        mat4 project = mat4(1.0f);
        project = perspective(radians(45.0f),
            (float)window.GetScreenWidth() / (float)window.GetScreenHeight(),
            0.01f, 100.0f);

        shader.SetMat4("VIEW", camera.GetViewMatrix());
        shader.SetMat4("PROJECTION", project);

        shader.SetBool("WIND", false);
        shader.SetFloat("WINDEFFECT", 0.2);

        for(int i = 0; i < sizeof(cubePositions)/sizeof(vec3); i++)
        {
            glm::mat4 transform = glm::mat4(1.0f);
            transform = glm::translate(transform, cubePositions[i]);
            transform = glm::scale(transform, glm::vec3(0.5f));

            shader.SetMat4("TRANSFORM", transform);

            Draw(cubeModel);
        }

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, grassTexture.id);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textureSpecular.id);

        shader.SetBool("WIND", true);

        for(vec3 pos : cubePositions)
        {
            glm::mat4 transform = glm::mat4(1.0f);
            transform = glm::translate(transform, pos + vec3(0.0f, 0.5f, 0.0f));
            transform = glm::scale(transform, glm::vec3(0.5f));

            shader.SetMat4("TRANSFORM", transform);

            Draw(grassModel);
        }

        shader.UnUse();

        window.SwapBuffer();
        lastTime = SDL_GetTicks();
        SDL_Delay(5);
    }

    return 0;
}