add_executable(simulation render.cpp window.cpp camera.cpp object.cpp loader.cpp triangle.cpp)

target_include_directories(simulation PUBLIC ../include)
target_link_libraries(simulation glfw glad glm)