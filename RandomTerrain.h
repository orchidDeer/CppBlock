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
#include <vector>

/**
 * Perlin noise for generation Terrain.
 */
class RandomTerrain {
public:
    RandomTerrain(int seed, int size);
    ~RandomTerrain();

    int perlinNoise(int x);
    static float fade(float t);
    float grad(float p);
    float noise(float p);

    int getSeed();

private:

    // mixed vector
    std::vector<int> permutation;
    int size, seed;
};

#endif //CMINECRAFT_RANDOMTERRAIN_H
