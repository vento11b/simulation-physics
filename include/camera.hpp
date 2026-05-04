#pragma once
#include <glm/glm.hpp>

class Camera {
public:
    glm::vec2 position;
    float speed;
    glm::mat4 getView();

};