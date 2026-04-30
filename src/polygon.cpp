#include "polygon.h"

Vec2 verts[] = {{ 0.0f,  0.5f},
                {-0.5f, -0.5f},
                { 0.5f, -0.5f}};
                
Polygon triangle = {
    .vertices = verts,
    .count = 3
};