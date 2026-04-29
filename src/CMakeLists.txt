add_executable(simulation main.c)


target_include_directories(simulation PRIVATE ../include/)
target_link_libraries(simulation glfw glad)