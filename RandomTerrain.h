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
class RandomTerrain {
public:
    RandomTerrain(int seed);
    ~RandomTerrain();

    int perlinNoise(int x);
    static float fade(float t);
    int grad(float p);
    float noise(float p);

    int getSeed() const;

private:

    int seed;

    float frequency[8]{};
    float amplitude[8]{};

    std::uniform_int_distribution<int> distribution;
    std::default_random_engine dre;
};

#endif //CMINECRAFT_RANDOMTERRAIN_H
