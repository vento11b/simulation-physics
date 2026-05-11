#include "world.hpp"
#include "particle.hpp"
#include <fstream>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

static GLuint loadComputeShader(const char* path) {
    std::ifstream file(path, std::ios::in | std::ios::binary);
    if (!file) { std::cerr << "Failed to open compute shader file\n"; return 0; }
    std::string src((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    GLuint shader = glCreateShader(GL_COMPUTE_SHADER);
    const char* srcPtr = src.c_str();
    glShaderSource(shader, 1, &srcPtr, nullptr);
    glCompileShader(shader);
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[512];
        glGetShaderInfoLog(shader, 512, nullptr, log);
        std::cerr << "Compute shader compile error: " << log << std::endl;
        return 0;
    }
    GLuint program = glCreateProgram();
    glAttachShader(program, shader);
    glLinkProgram(program);
    glDeleteShader(shader);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char log[512];
        glGetProgramInfoLog(program, 512, nullptr, log);
        std::cerr << "Compute shader link error: " << log << std::endl;
        return 0;
    }
    return program;
}

World::World() {
    computeShader = loadComputeShader("./shaders/physics.comp");
}
World::~World() {
    if (ssbo) glDeleteBuffers(1, &ssbo);
    if (computeShader) glDeleteProgram(computeShader);
}
void World::addObject(const Particle& obj) {
    objects.push_back(obj);
}
void World::syncToGPU() {
    if (ssbo == 0) glGenBuffers(1, &ssbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, objects.size() * sizeof(Particle), objects.data(), GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}
void World::stepPhysics() {
    syncToGPU();
    glUseProgram(computeShader);
    glUniform1f(glGetUniformLocation(computeShader, "dt"), dt);
    glUniform1f(glGetUniformLocation(computeShader, "gravity"), gravity);
    glDispatchCompute((GLuint)objects.size(), 1, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    syncFromGPU();
}
void World::syncFromGPU() {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    void* ptr = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY);
    if (ptr) {
        memcpy(objects.data(), ptr, objects.size() * sizeof(Particle));
        glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
    }
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}
void World::fillBatch(Batch& batch) {
    batch.instances.clear();
    for (const auto& obj : objects) {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(obj.position, 0.0f));
        model = glm::scale(model, glm::vec3(obj.scale, 1.0f));
        batch.addInstance(model, obj.color);
    }
    batch.updateInstanceBuffer();
}
