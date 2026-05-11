#include "shader.hpp"
#include <cstdio>
#include <vector>

Shader::Shader(unsigned int _type, const char* _filename) : type(_type), filename(_filename) {
    std::printf("B\n");
    FILE* file = fopen(filename, "rb");
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);
    

    char* buffer = new char[size + 1];
    if (!buffer) {
        fclose(file);
        source = NULL;
    }

    fread(buffer, 1, size, file);

    buffer[size] = '\0';

    source = buffer;
}

Shader::Shader(std::vector<Shader*> _sub_shaders) {
    for (Shader* i : _sub_shaders) sub_shaders.push_back(i);
}

Shader::Shader(Shader* _sub_shader) {
    sub_shaders.push_back(_sub_shader);
}

void Shader::use() {
    if (!linked) {
        compile();
        link();
        linked = true;
    }
    glUseProgram(program);
}

void Shader::setMat4(const char* name, glm::mat4& m) {
    glUniformMatrix4fv(glGetUniformLocation(program, name), 1, GL_FALSE, &m[0][0]);
}

void Shader::setVec3(const char* name, glm::vec<3, unsigned char>& v) {
    glUniform3f(glGetUniformLocation(program, name), v.x, v.y, v.z);
}

int Shader::compile() {
    if (source==NULL) {
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
    }
    else {
        program = glCreateShader(type);
        glShaderSource(program, 1, &source, NULL);
        glCompileShader(program);


        int success;
        char infoLog[512];
        glGetShaderiv(program, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(program, 512, NULL, infoLog);
            std::printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
            return -2;
        }
    }
    return 0;
}
    
int Shader::link() {
    program = glCreateProgram();
    for (Shader* sub_shader : sub_shaders)
        glAttachShader(program, sub_shader->program);

    glLinkProgram(program);
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
        return -2;
    }

    for (Shader* sub_shader : sub_shaders)
        glDeleteShader(sub_shader->program);

    return 0;
}

void Shader::add_shader(Shader* _sub_shader) {
    sub_shaders.push_back(_sub_shader);
}