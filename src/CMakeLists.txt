add_executable(simulation render.cpp window.cpp loader.cpp camera.cpp object.cpp shader.cpp circle.cpp)

target_include_directories(simulation PUBLIC ../include)
target_link_libraries(simulation glfw glad glm)