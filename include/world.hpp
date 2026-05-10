#pragma once
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "batch.hpp"
#include "circle.hpp"


class World {
public:
    std::vector<Circle> objects;
    GLuint ssbo = 0;
    GLuint computeShader = 0;
    float gravity = -500.0f;
    float dt = 1.0f / 60.0f;

    World();
    ~World();
    void addObject(const Circle& obj);
    void syncToGPU();
    void stepPhysics();
    void syncFromGPU();
    void fillBatch(Batch& batch);
};
