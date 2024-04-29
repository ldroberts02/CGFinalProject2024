#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#pragma once

namespace Canis
{
    class Map
    {
    public:
        std::vector<std::vector<std::vector<unsigned int>>> LoadMap(std::string _path);
    };
}
