#include "RandomTerrain.h"

RandomTerrain::RandomTerrain(int seed) : distribution(-1, 1), dre(seed) {
    this->seed = seed;

    for (int i = 0; i < 8; ++i) {
        frequency[i] = float(distribution(dre));
        amplitude[i] = float(distribution(dre));
    }
}

RandomTerrain::~RandomTerrain() = default;

float RandomTerrain::fade(float t) {
    return float(t*t*t*(t*(t*6.0 - 15.0) + 10.0));
}

int RandomTerrain::grad(float d) {
    dre.seed(long(long(d * 1000) + seed));
    return distribution(dre);
}

float RandomTerrain::noise(float d) {
    float p0 = floorf(d);
    float p1 = p0 + 1.0f;

    float t = d - p0;
    float fade_t = fade(t);

    auto g0 = float(grad(p0));
    auto g1 = float(grad(p1));

    return float((1.0 - fade_t) * g0 * (d - p0) + fade_t * g1 * (d - p1));
}

int RandomTerrain::perlinNoise(int x) {

    float n = noise(float(x) * (frequency[0] * 0.01f)) * (20.f * amplitude[0]) +
              noise(float(x) * (frequency[1] * 0.001f)) * (50.f * amplitude[1]) +
              noise(float(x) * (frequency[2] * 0.02f)) * (10.f * amplitude[2]) +
              noise(float(x) * (frequency[3] * 1.f)) * (8.f * amplitude[3]) +
              noise(float(x) * (frequency[4] * 0.03f)) * (9.f * amplitude[4]) +
              noise(float(x) * (frequency[5] * 0.00002f)) * (100.f * amplitude[5]) +
              noise(float(x) * (frequency[6] * 0.00345f)) * (30.f * amplitude[6]) +
              noise(float(x) * (frequency[7] * 0.00432f)) * (12.f * amplitude[7]);

    return int(n);
}

int RandomTerrain::getSeed() const {
    return seed;
}
