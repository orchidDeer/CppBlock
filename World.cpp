#include "World.h"

#define CHUNKSIZE 1000

World::World(int height, int seed) : perlinNoise(seed) {
    this->worldHeight = height;
    this->worldSeed = seed;
}

World::~World() {
    //change.clear();
}

int World::getTerrainHeight(int x) {

    int height;

    // switch to next chunk and make a new perlin noise
    if(worldSeed + int(x / CHUNKSIZE) != perlinNoise.getSeed()) {
        perlinNoise = RandomTerrain(worldSeed + int(x / CHUNKSIZE));
    }

    // Get terrain height from perlin noise
    height = worldHeight / 2 - perlinNoise.perlinNoise(x - (CHUNKSIZE * (x / CHUNKSIZE)));

    // Interpolate between different perlin noise if needed to make smooth edges
    if(x > (int(x / CHUNKSIZE) + 1) * CHUNKSIZE - 30) {
        // Calculate bias for interpolation
        float w = float((int(x / CHUNKSIZE) + 1) * CHUNKSIZE - x) / 30.f;
        // Interpolate
        height = interpolate(height, getTerrainHeight((x / CHUNKSIZE + 1) * CHUNKSIZE), w);
    }

    return height;
}

std::vector<short int> World::createNext(int x, int maxY, int minY) {
    // Vector of world segment
    std::vector<short int> line;
    // Resize vector to fit the requested range
    line.resize(maxY - minY);

    // Get height of the world floor for the specific segment
    int height = getTerrainHeight(x);

    // Write data to world segment
    for (int i = minY; i < maxY; ++i) {
        if(i > height) {
            line[i - minY] = 0;
        } else {
            line[i - minY] = 1;
        }
    }

    return line;
}

int World::interpolate(int h0, int h1, float w) {

    // Clips ends
    if (0.04f > w)
        return h1;
    else if (0.95f < w)
        return h0;

    // Interpolation
    return std::ceil(float(h0 - h1) * ((w * (w * 6.f - 15.f) + 10.f) * w * w * w) + float(h1));
}
