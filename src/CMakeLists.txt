add_executable(simulation main.cpp)

target_include_directories(simulation PUBLIC ../include)
target_link_libraries(simulation glfw glad)