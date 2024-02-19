#pragma once
#include <string>
#include "Data/GLTexture.hpp"

namespace Canis
{
    extern GLTexture LoadImageGL(std::string _path);

	extern GLTexture LoadImageGL(std::string _path, int _sourceFormat, int _format);
} // end of Canis namespace