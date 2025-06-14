add_library(PacLib world.cc worldentity.cc simplecollidercomponent.cc rectanglerenderer.cc immovablerect.cc gravitycomponent.cc pelletentity.cc)

add_subdirectory(libs/raylib)
target_link_libraries(PacLib PUBLIC raylib)
