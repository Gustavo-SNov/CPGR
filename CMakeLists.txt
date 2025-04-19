cmake_minimum_required(VERSION 3.30)
project(CPGR)

set(CMAKE_CXX_STANDARD 20)

# Adiciona os diretórios das bibliotecas
include_directories(
            C:/libs_c++/GLFW/include
            C:/libs_c++/GLAD/include
            ${PROJECT_SOURCE_DIR}/include)

link_directories(C:/libs_c++/GLFW/lib C:/libs_c++/GLAD/lib)

add_executable(CPGR main.cpp
        C:/libs_c++/GLAD/src/glad.c
        src/Triangle.cpp
        src/Transformation.cpp)

# Linkando as bibliotecas
target_link_libraries(CPGR glfw3 opengl32 gdi32 glu32)