//
// Created by maxim on 08/05/2021.
//

#ifndef CMINECRAFT_RANDOMTERRAIN_H
#define CMINECRAFT_RANDOMTERRAIN_H

#include <algorithm>
#include <iostream>
#include <list>
#include <numeric>
#include <random>
#include <functional>
#include <vector>

/**
 * Perlin noise for generation Terrain.
 */
class PerlinNoise {
public:
    PerlinNoise();
    ~PerlinNoise();

    static float fade(float t);
    int grad(float d, int seed);
    float noise(int d, float frequency, float amplitude, int seed);

private:
    std::uniform_int_distribution<int> distribution;
    std::default_random_engine dre;
};

#endif //CMINECRAFT_RANDOMTERRAIN_H
