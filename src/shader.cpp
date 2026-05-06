#include "shader.hpp"
#include <cstdio>

void Shader::use() {
    glUseProgram(program);
}

void Shader::setMat4(const char* name, glm::mat4& m) {
    glUniformMatrix4fv(glGetUniformLocation(program, name), 1, GL_FALSE, &m[0][0]);
}

int Shader::compile() {
    for (Shader* sub_shader : sub_shaders) {
        sub_shader->program = glCreateShader(sub_shader->type);
        glShaderSource(sub_shader->program, 1, &sub_shader->source, NULL);
        glCompileShader(sub_shader->program);
        
        int success;
        char infoLog[512];
        glGetShaderiv(sub_shader->program, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(sub_shader->program, 512, NULL, infoLog);
            std::printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
            return -1;
        }
    }
    return 0;
}
    
int Shader::link() {
    for (Shader* sub_shader : sub_shaders) {
        if (0) return -1;
        glAttachShader(program, sub_shader->program);
        
        int success;
        char infoLog[512];
        glGetProgramiv(sub_shader->program, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(sub_shader->program, 512, NULL, infoLog);
            std::printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
            return -2;
        }
        glDeleteShader(sub_shader->program);
    }
}