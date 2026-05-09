#pragma once
#include <vector>
#include "window.hpp"
#include "camera.hpp"
#include "object.hpp"


class EntitySystem {
public:
    void load();
    
    void draw();
    void draw(Window window);

    std::vector<Object*> entities;
};