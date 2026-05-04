cmake_minimum_required(VERSION 3.15)
project(simulation C CXX)

include(FetchContent)


FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.9
)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG 5bf3eda
)
FetchContent_MakeAvailable(glad)
add_library(glad ${glad_SOURCE_DIR}/src/glad.c)
target_include_directories(glad PUBLIC ${glad_SOURCE_DIR}/include)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.3
)
FetchContent_MakeAvailable(glm)

#add_subdirectory(${CMAKE_SOURCE_DIR}/lib/glfw-3.4)
add_subdirectory(src)

