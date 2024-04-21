#include "World.hpp"
#include <SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

namespace Canis
{
    World::World(Window *_window, InputManager *_inputManager)
    {
        m_window = _window;
        m_inputManager = _inputManager;
    }

    void World::Update()
    {
        UpdateCameraMovement();
    }

    void World::Draw()
    {
        for (int i = 0; i < m_entities.size(); i++)
        {
            Shader *shader = m_entities[i].shader;
            shader->Use();
            shader->SetVec3("COLOR", 1.0f, 1.0f, 1.0f);
            shader->SetVec3("VIEWPOS", m_camera.Position);
            shader->SetInt("NUMBEROFPOINTLIGHTS", 4);
            shader->SetFloat("TIME", SDL_GetTicks() / 1000.0f);

            UpdatePointLight(*shader, m_pointLights[0], 0);
            UpdatePointLight(*shader, m_pointLights[1], 1);
            UpdatePointLight(*shader, m_pointLights[2], 2);
            UpdatePointLight(*shader, m_pointLights[3], 3);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_entities[i].albedo->id);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, m_entities[i].specular->id);

            shader->SetInt("MATERIAL.diffuse", 0);
            shader->SetInt("MATERIAL.specular", 1);
            shader->SetFloat("MATERIAL.shininess", 64);

            mat4 project = mat4(1.0f);
            project = perspective(radians(45.0f),
                                  (float)m_window->GetScreenWidth() / (float)m_window->GetScreenHeight(),
                                  0.01f, 100.0f);

            shader->SetMat4("VIEW", m_camera.GetViewMatrix());
            shader->SetMat4("PROJECTION", project);

            shader->SetMat4("TRANSFORM", m_entities[i].transform.Matrix());
            Canis::Draw(*m_entities[i].model);
            shader->UnUse();
        }
    }

    void World::Spawn(Entity _entity)
    {
        m_entities.push_back(_entity);
    }

    void World::SpawnPointLight(PointLight _light)
    {
        m_pointLights.push_back(_light);
    }

    void World::SpawnDirectionalLight(DirectionalLight _light)
    {
        m_directionalLight = _light;
    }

    Entity *World::GetEntityWithTag(std::string _tag)
    {
        for (int i = 0; i < m_entities.size(); i++)
        {
            if (m_entities[i].tag == _tag)
            {
                return &m_entities[i];
            }
        }

        return nullptr;
    }

    std::vector<Entity *> World::GetEntitiesWithTag(std::string _tag)
    {
        std::vector<Entity *> matches = {};

        for (int i = 0; i < m_entities.size(); i++)
        {
            if (m_entities[i].tag == _tag)
            {
                matches.push_back(&m_entities[i]);
            }
        }

        return matches;
    }

    void World::UpdatePointLight(Canis::Shader &_shader, Canis::PointLight &_pointLight, int _index)
    {
        _shader.SetVec3("POINTLIGHTS[" + std::to_string(_index) + "].position", _pointLight.position);
        _shader.SetVec3("POINTLIGHTS[" + std::to_string(_index) + "].ambient", _pointLight.ambient);
        _shader.SetVec3("POINTLIGHTS[" + std::to_string(_index) + "].diffuse", _pointLight.diffuse);
        _shader.SetVec3("POINTLIGHTS[" + std::to_string(_index) + "].specular", _pointLight.specular);
        _shader.SetFloat("POINTLIGHTS[" + std::to_string(_index) + "].constant", _pointLight.constant);
        _shader.SetFloat("POINTLIGHTS[" + std::to_string(_index) + "].linear", _pointLight.linear);
        _shader.SetFloat("POINTLIGHTS[" + std::to_string(_index) + "].quadratic", _pointLight.quadratic);
    }

    void World::UpdateCameraMovement()
    {
        if (m_inputManager->GetKey(SDL_SCANCODE_W))
            m_camera.ProcessKeyboard(Canis::Camera_Movement::FORWARD, 0.0016f);

        if (m_inputManager->GetKey(SDL_SCANCODE_S))
            m_camera.ProcessKeyboard(Canis::Camera_Movement::BACKWARD, 0.0016f);

        if (m_inputManager->GetKey(SDL_SCANCODE_A))
            m_camera.ProcessKeyboard(Canis::Camera_Movement::LEFT, 0.0016f);

        if (m_inputManager->GetKey(SDL_SCANCODE_D))
            m_camera.ProcessKeyboard(Canis::Camera_Movement::RIGHT, 0.0016f);

        if (m_window->GetMouseLock())
            m_camera.ProcessMouseMovement(m_inputManager->mouseRel.x, -m_inputManager->mouseRel.y, true);

        if (m_inputManager->JustPressedKey(SDLK_ESCAPE))
            m_window->MouseLock(!m_window->GetMouseLock());
    }
}