#pragma once
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "batch.hpp"
#include "particle.hpp"


class World {
public:
    std::vector<Particle> objects;
    GLuint ssbo = 0;
    GLuint computeShader = 0;
    float gravity = -500.0f;
    float dt = 1.0f / 60.0f;

    World();
    ~World();
    void addObject(const Particle& obj);
    void syncToGPU();
    void stepPhysics();
    void syncFromGPU();
    void fillBatch(Batch& batch);
};
