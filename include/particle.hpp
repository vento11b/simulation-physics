#pragma once
#include <glm/glm.hpp>
#include "object.hpp"

class Particle : public Object {
public:
    //Particle(glm::vec2 _position = glm::vec2(0,0), glm::vec2 _scale = glm::vec2(300,300), float _rotation = 0, int _divisions = 6);

    Particle(glm::vec2 _position, float _radius, float _rotation, glm::vec<3, unsigned char> _color, int _divisions, Shader* _shader = &default_shader);

    Particle(glm::vec2 _position, float _radius, int _divisions) : Particle(_position, _radius, 0, glm::vec<3, unsigned char>{0, 0, 255}, _divisions) {};
    Particle(glm::vec2 _position, float _radius, glm::vec<3, unsigned char> _color, int _divisions) : Particle(_position, _radius, 0, _color, _divisions) {};
    Particle(glm::vec2 _position, float _radius) : Particle(_position, _radius, 0, glm::vec<3, unsigned char>{0, 0, 255}, 6) {};
    Particle(glm::vec2 _position, float _radius, glm::vec<3, unsigned char> _color) : Particle(_position, _radius, 0, _color, 6) {};
    Particle(glm::vec2 _position, int _divisions) : Particle(_position, 2.8e-15f, 0, glm::vec<3, unsigned char>{0, 0, 255}, _divisions) {};
    Particle(glm::vec2 _position) : Particle(_position, 2.8e-15f, 0, glm::vec<3, unsigned char>{0, 0, 255}, 6) {};
    Particle(int _divisions) : Particle(glm::vec2(0,0), 2.8e-15f, 0, glm::vec<3, unsigned char>{0, 0, 255}, _divisions) {};
    Particle(Shader* _shader) : Particle(glm::vec2(0,0), 2.8e-15f, 0, glm::vec<3, unsigned char>{0, 0, 255}, 6, _shader) {};
    Particle() : Particle(glm::vec2(0,0), 2.8e-15f, 0, glm::vec<3, unsigned char>{0, 0, 255}, 6) {};
//private:
    int divisions = 6;
    float radius = 2.8e-15f;
    float charge = 1.60217646e-19f;
};