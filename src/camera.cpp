#include "camera.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

glm::mat4 Camera::getView() {
    return glm::translate(glm::mat4(1.0f), glm::vec3(-position, 0.0f));
}
