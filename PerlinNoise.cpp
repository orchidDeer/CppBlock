#include "PerlinNoise.h"

PerlinNoise::PerlinNoise() : distribution(-1, 1) {

}

PerlinNoise::~PerlinNoise() = default;

float PerlinNoise::fade(float t) {
    return float(t*t*t*(t*(t*6.0 - 15.0) + 10.0));
}

int PerlinNoise::grad(float d, int seed) {
    dre.seed(long(long(d * 1000) + seed));
    return distribution(dre);
}

float PerlinNoise::noise(int d, float frequency, float amplitude, int seed) {
    float p = float(d) * frequency;

    float p0 = floorf(p);
    float p1 = p0 + 1.0f;

    float t = p - p0;
    float fade_t = fade(t);

    auto g0 = float(grad(p0, seed));
    auto g1 = float(grad(p1, seed));

    float noise = (1.f - fade_t) * g0 * (p - p0) + fade_t * g1 * (p - p1);

    return (noise * amplitude);
}
