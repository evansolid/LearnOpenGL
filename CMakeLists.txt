cmake_minimum_required(VERSION 4.1.1)
project(LearnOpenGL)

add_executable(cutable 
    src/main.cpp
    src/glad.c
)

target_include_directories(cutable   PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_directories(cutable PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

target_link_libraries(cutable PRIVATE
    glfw3dll
    opengl32
)

set_target_properties(cutable PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)