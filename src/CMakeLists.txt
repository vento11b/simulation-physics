add_executable(simulation render.cpp window.cpp camera.cpp shader.cpp object.cpp circle.cpp entitysystem.cpp)

target_include_directories(simulation PUBLIC ../include)
target_link_libraries(simulation glfw glad glm)