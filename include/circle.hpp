#pragma once
#include <glm/glm.hpp>
#include "object.hpp"

class Circle : public Object {
public:
    //Circle(glm::vec2 _position = glm::vec2(0,0), glm::vec2 _scale = glm::vec2(300,300), float _rotation = 0, int _divisions = 6);

    Circle(glm::vec2 _position, glm::vec2 _scale, float _rotation, int _divisions);
    Circle(glm::vec2 _position, glm::vec2 _scale, int _divisions) : Circle(_position, _scale, 0, _divisions) {};
    Circle(glm::vec2 _position, glm::vec2 _scale) : Circle(_position, _scale, 0, 6) {};
    Circle(glm::vec2 _position, int _divisions) : Circle(_position, glm::vec2(200,200), 0, _divisions) {};
    Circle(glm::vec2 _position) : Circle(_position, glm::vec2(200,200), 0, 6) {};
    Circle(int _divisions) : Circle(glm::vec2(0,0), glm::vec2(200,200), 0, _divisions) {};
    Circle() : Circle(glm::vec2(0,0), glm::vec2(200,200), 0, 6) {};
private:
    float radius;
    int divisions;
};