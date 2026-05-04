#pragma once
#include <cstdlib>

template <typename T_values, std::size_t... sizes>
struct Vertex {
    template <typename T_values, std::size_t N_values>
    struct VertexAttribute {
        T_values values[N_values];
    };
    
    std::size_t sizes[] = {sizes...}
    VertexAttribute<T_values, N_values> attributes[sizeof(sizes)];
};
