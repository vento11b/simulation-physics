#pragma once
#include <cstdlib>
#include <tuple>
#include <vertex.hpp>

template <typename... vertices>
struct Mesh {
    std::tuple<vertices>;
    vertices N_attributes[] = {N_attributes...}
    Vertex<T_values, ...sizes> vertex[sizeof(N_attributes)];
};
