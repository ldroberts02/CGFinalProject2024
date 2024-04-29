#include "Map.hpp"
#include "Debug.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#pragma once

namespace Canis
{
    std::vector<std::vector<std::vector<unsigned int>>> LoadMap(std::string _path)
    {
        return {};
        /*std::vector<std::vector<std::vector<unsigned int>>> map = {};
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
        return map;*/
    }
}