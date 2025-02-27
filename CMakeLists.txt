cmake_minimum_required(VERSION 3.10)
project(OpenGL_BlackHole_Simulation)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

add_executable(particles
    src/main.cpp
    src/ParticleSystem.cpp
    src/ShaderProgram.cpp
)

target_include_directories(particles PRIVATE ${OPENGL_INCLUDE_DIRS})
target_link_libraries(particles PRIVATE glfw OpenGL::GL)

if(APPLE)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(CORE_FOUNDATION_LIBRARY CoreFoundation)
    target_link_libraries(particles PRIVATE
        ${COCOA_LIBRARY}
        ${IOKIT_LIBRARY}
        ${CORE_FOUNDATION_LIBRARY}
    )
endif()
