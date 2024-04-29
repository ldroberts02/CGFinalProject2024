#include <vector>
#include "World.hpp"

using namespace glm;

namespace Canis
{
    class Lights
    {
    public:
        void SpawnLights(Canis::World _world); //, std::vector<glm::vec3> _dynamicLightsPositons
        std::vector<glm::vec3> dynamicLightsPositions;
    };
}