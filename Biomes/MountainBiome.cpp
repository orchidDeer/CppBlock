#include "MountainBiome.h"

MountainBiome::MountainBiome(int seed, std::uniform_int_distribution<int> &distribution,
                             std::default_random_engine &dre) {
    dre.seed(seed);

    this->seed = seed;

    // Randomise frequency and amplitude of functions
    //                            Random Number between 0 and 1      multiplier           Base
    this->frequency[0] = (float(distribution(dre)) / 100.f)      * 0.005f            + 0.01f;
    this->amplitude[0] = (float(distribution(dre)) / 100.f)      * 5.f               + 15.f;

    this->frequency[1] = (float(distribution(dre)) / 100.f)      * 0.0005f           + 0.005f;
    this->amplitude[1] = (float(distribution(dre)) / 100.f)      * 10.f              + 60.f;

    this->frequency[2] = (float(distribution(dre)) / 100.f)      * 0.005f            + 0.02f;
    this->amplitude[2] = (float(distribution(dre)) / 100.f)      * 20.f              + 10.f;

    this->frequency[3] = (float(distribution(dre)) / 100.f)      * 0.005f            + 0.009f;
    this->amplitude[3] = (float(distribution(dre)) / 100.f)      * 10.f              + 8.f;

    this->frequency[4] = (float(distribution(dre)) / 100.f)      * 0.005f            + 0.03f;
    this->amplitude[4] = (float(distribution(dre)) / 100.f)      * 10.f              + 9.f;

    this->frequency[5] = (float(distribution(dre)) / 100.f)      * 0.00001f          + 0.00002f;
    this->amplitude[5] = (float(distribution(dre)) / 100.f)      * 10.f              + 100.f;

    this->frequency[6] = (float(distribution(dre)) / 100.f)      * 0.005f            + 0.00345f;
    this->amplitude[6] = (float(distribution(dre)) / 100.f)      * 10.f              + 30.f;

    this->frequency[7] = (float(distribution(dre)) / 100.f)      * 0.005f            + 0.00432f;
    this->amplitude[7] = (float(distribution(dre)) / 100.f)      * 10.f              + 12.f;
}

Segment MountainBiome::generateSegmentView(int x, int &minY, int &maxY, int &height, int chunkSize) {
    Segment segment;

    // Calculate height from functions
    segment.height = int(std::abs(perlinNoise.noise(x, frequency[0], amplitude[0], seed)) +
                         std::abs(perlinNoise.noise(x, frequency[1], amplitude[1], seed)) +
                         std::abs(perlinNoise.noise(x, frequency[2], amplitude[2], seed)) +
                         std::abs(perlinNoise.noise(x, frequency[3], amplitude[3], seed)) +
                         std::abs(perlinNoise.noise(x, frequency[4], amplitude[4], seed)) +
                         std::abs(perlinNoise.noise(x, frequency[5], amplitude[5], seed)) +
                         std::abs(perlinNoise.noise(x, frequency[6], amplitude[6], seed)) +
                         std::abs(perlinNoise.noise(x, frequency[7], amplitude[7], seed)));

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

MountainBiome::~MountainBiome() = default;
