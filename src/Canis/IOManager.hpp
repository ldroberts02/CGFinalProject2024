#pragma once
#include <string>
#include "Data/GLTexture.hpp"

namespace Canis
{
    extern GLTexture LoadImageGL(std::string _path);

    extern GLTexture LoadImageGL(std::string _path, int _sourceFormat, int _format);

    extern bool LoadOBJ(std::string path,
                        std::vector<glm::vec3> &out_vertices,
                        std::vector<glm::vec2> &out_uvs,
                        std::vector<glm::vec3> &out_normals);
} // end of Canis namespace