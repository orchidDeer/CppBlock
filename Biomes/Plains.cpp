#include "Plains.h"

Plains::Plains(int seed, std::uniform_int_distribution<int> &distribution,
               std::default_random_engine &dre) {
    dre.seed(seed);

    this->seed = seed;

    // Randomise frequency and amplitude of functions
    //                            Random Number between 0 and 1     multiplier           Base
    this->frequency[0] = (float(distribution(dre)) / 100.f)     * 0.005f            + 0.01f;
    this->amplitude[0] = (float(distribution(dre)) / 100.f)     * 3.f               + 1.f;

    this->frequency[1] = (float(distribution(dre)) / 100.f)     * 0.0005f           + 0.005f;
    this->amplitude[1] = (float(distribution(dre)) / 100.f)     * 4.f               + 2.f;

    this->frequency[2] = (float(distribution(dre)) / 100.f)     * 0.005f            + 0.02f;
    this->amplitude[2] = (float(distribution(dre)) / 100.f)     * 2.f               + 3.f;
}

Plains::~Plains() = default;

Segment Plains::generateSegmentView(int x, int &minY, int &maxY, int &height, int chunkSize) {
    Segment segment;

    // Calculate height from functions
    segment.height = int(perlinNoise.noise(x, frequency[0], amplitude[0], seed) +
                         perlinNoise.noise(x, frequency[1], amplitude[1], seed) +
                         perlinNoise.noise(x, frequency[2], amplitude[2], seed));

    // Move function middle to screen middle
    segment.height = height / 2 - segment.height;

    // Interpolate 30 segments before next chunk
    if(x > (int(x / chunkSize) + 1) * chunkSize - 30) {
        // Calculate bias for interpolation
        float w = float((int(x / chunkSize) + 1) * chunkSize - x) / 30.f;
        // Interpolate TODO: Interpolate without going to 75 on both sides
        segment.height = interpolate(segment.height, 75, w);
    }

    // Get segment data if requested
    if(!(minY == 0 && maxY == 0))
        segment.data = terrain(segment.height, minY, maxY);

    return segment;
}
