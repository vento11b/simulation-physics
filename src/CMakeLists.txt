add_executable(simulation   render.cpp
                            window.cpp
                            camera.cpp
                            mesh.cpp
                            shader.cpp
                            object.cpp
                            particle.cpp
                            entitysystem.cpp
                            
                            ui/ui.cpp
                            ui/imgui.cpp
                            ui/imgui_draw.cpp
                            ui/imgui_tables.cpp
                            ui/imgui_widgets.cpp
                            ui/backends/imgui_impl_glfw.cpp
                            ui/backends/imgui_impl_opengl3.cpp)

target_include_directories(simulation PRIVATE ../include ../include/ui ../include/ui/backends)
target_link_libraries(simulation glfw glad glm)