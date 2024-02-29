#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace objects2D
{

    // Create wallpaper 
    Mesh* CreateRectangle(const std::string &name, glm::vec3 leftBottomCorner, float height, float width, glm::vec3 color, bool fill = false);
    Mesh* CreateDiamond(const std::string& name, glm::vec3 center, float height, float width, glm::vec3 color, bool fill);
    Mesh* CreateRectangleEmpty(const std::string& name, glm::vec3 leftBottomCorner, float height, float width, glm::vec3 color);
    Mesh* CreateHexagon(const std::string& name, glm::vec3 center, float size, glm::vec3 color, bool fill);
    Mesh* CreatePoligon(const std::string& name, glm::vec3 center, float size, glm::vec3 color, bool fill);
    Mesh* CreateStar(const std::string& name, glm::vec3 center, float size, glm::vec3 color, bool fill);

}
