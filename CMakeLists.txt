cmake_minimum_required(VERSION 3.19)
project(CppBlock)

set(CMAKE_CXX_STANDARD 14)

add_executable( CppBlock main.cpp World.cpp World.h PerlinNoise.h PerlinNoise.cpp
                View.cpp View.h compatibility.cpp compatibility.h Biomes/Biome.h
                Biomes/Biome.cpp Biomes/MountainBiome.cpp Biomes/MountainBiome.h
                Biomes/Plains.cpp Biomes/Plains.h)