cmake_minimum_required(VERSION 3.19)
project(CppBlock)

set(CMAKE_CXX_STANDARD 14)

add_executable( CMinecraft main.cpp World.cpp World.h RandomTerrain.h RandomTerrain.cpp
                View.cpp View.h compatibility.cpp compatibility.h)