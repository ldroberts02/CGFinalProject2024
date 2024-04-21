#pragma once
#include <vector>
#include "Camera.hpp"
#include "Entity.hpp"
#include "Window.hpp"
#include "InputManager.hpp"
#include "Data/PointLight.hpp"
#include "Data/DirectionalLight.hpp"

namespace Canis
{
    class World
    {
    public:
        World(Window *_window, InputManager *_inputManager);
        void Update(double _deltaTime);
        void Draw(double _deltaTime);
        void Spawn(Entity _entity);
        void SpawnPointLight(PointLight _light);
        void SpawnDirectionalLight(DirectionalLight _light);
        Entity* GetEntityWithTag(std::string _tag);
        std::vector<Entity*> GetEntitiesWithTag(std::string _tag);
    private:
        InputManager *m_inputManager;
        Window *m_window;
        Camera m_camera = Camera(glm::vec3(0.0f, 0.0f, -3.0f));
        DirectionalLight m_directionalLight;
        std::vector<Entity> m_entities = {};
        std::vector<PointLight> m_pointLights = {};

        void UpdateLights(Canis::Shader &_shader);
        void UpdateCameraMovement();
    };
}