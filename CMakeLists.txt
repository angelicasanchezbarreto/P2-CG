cmake_minimum_required(VERSION 3.25)
project(P2-CG)

set(CMAKE_CXX_STANDARD 17)

add_executable(P2-CG main.cpp glad.c glut_ply.cpp Objeto.cpp SistemaSolar.cpp BoundingVolume.h)

target_link_libraries(P2-CG -lOpenGL32 -lGLU32 -lfreeGLUT -lglfw3)