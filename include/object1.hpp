#pragma once
#include "mesh.hpp"

template <typename T = Mesh>
struct Object {
    T *mesh;
}