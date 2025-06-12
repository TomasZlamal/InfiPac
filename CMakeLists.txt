cmake_minimum_required(VERSION 3.12)
project(Pac VERSION 0.2)

add_executable(Pac main.cc)


option(DEBUG_MODE "Use debug mode?" OFF)

target_include_directories(Pac PUBLIC
                           "${PROJECT_BINARY_DIR}")

add_subdirectory(src)

target_link_libraries(Pac PUBLIC raylib)
target_link_libraries(Pac PUBLIC PacLib)
target_include_directories(Pac PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/src/libs"
                          )
if (DEBUG_MODE)
  target_compile_definitions(Pac PUBLIC "DEBUG_MODE_ON")
  target_compile_definitions(PacLib PUBLIC "DEBUG_MODE_ON")
endif()

