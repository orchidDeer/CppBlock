//
// Created by maxim on 08/05/2021.
//

#include "RandomTerrain.h"

RandomTerrain::RandomTerrain(int seed, int size) {
    this->size = size;

    permutation.resize(size);

    // Fill permutation with values form 0 to size
    std::iota(permutation.begin(), permutation.end(), 0);

    std::default_random_engine engine(seed);

    std::shuffle(permutation.begin(), permutation.end(), engine);

    // Duplicate permutation vector
    permutation.insert(permutation.end(), permutation.begin(), permutation.end());
}

RandomTerrain::~RandomTerrain() {
    permutation.clear();
}

float RandomTerrain::fade(float t) {
    return float(t*t*t*(t*(t*6.0 - 15.0) + 10.0));
}

float RandomTerrain::grad(float d) {
    return this->permutation[int(floorf(d))] > size / 2 ? 1.0 : -1.0;
}

float RandomTerrain::noise(float d) {
    float p0 = floorf(d);
    float p1 = p0 + 1.0f;

    float t = d - p0;
    float fade_t = fade(t);

    float g0 = grad(p0);
    float g1 = grad(p1);

    return float((1.0 - fade_t) * g0 * (d - p0) + fade_t * g1 * (d - p1));
}

int RandomTerrain::perlinNoise(int x) {

    float n = noise(float(x) * 0.01f) * 20.f +
              noise(float(x) * 0.02f) * 10.f +
              noise(float(x) * 1.f) * 8.f;

    return int(n);
}
