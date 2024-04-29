#include "Lights.hpp"
#include "World.hpp"
#include "Debug.hpp"
#include <vector>

using namespace glm;

namespace Canis
{
    void Lights::SpawnLights(Canis::World _world) //, std::vector<glm::vec3> _dynamicLightsPositons
    {
        Canis::DirectionalLight directionalLight;
        _world.SpawnDirectionalLight(directionalLight);

        // testEnt = World::GetEntitiesWithTag(std::string _tag);

        // Start of light 1
        //_world.NumberOfLights += 1; // adds 1 to number of lights, the number is required for the shader, so if it is black, the number may be invalid.
        Canis::PointLight pointLight;
        pointLight.position = vec3(0.0f);
        pointLight.ambient = vec3(1.0f);
        pointLight.diffuse = vec3(0.4f);
        pointLight.specular = vec3(0.5f);
        pointLight.constant = 1.0f;
        pointLight.linear = 0.09f;
        pointLight.quadratic = 0.032f;
        _world.SpawnPointLight(pointLight);
        // End of light 1

        /*pointLight.position = vec3(0.0f, 0.0f, 0.0f); //_dynamicLightsPositions[0]
        pointLight.ambient = vec3(1.0f, 1.0f, 1.0f);
        _world.NumberOfLights += 1;
        _world.SpawnPointLight(pointLight);*/
    }
}