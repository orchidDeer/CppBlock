#include "World.h"

World::World(int height, int seed) {
    this->worldHeight = height;
    this->worldSeed = seed;

    perlinNoise[0] = RandomTerrain(seed, 255);
    perlinNoise[1] = RandomTerrain(seed + 1, 255);
}

World::~World() {
    //change.clear();
}

int World::getTerrainHeight(int x) {
    return worldHeight / 2 - perlinNoise[(x / 255) % 2].perlinNoise(x - (255 * (x / 255)));
}

std::vector<short int> World::createNext(int x, int maxY, int minY) {
    // Vector of world segment
    std::vector<short int> line;
    // Resize vector to fit the requested range
    line.resize(maxY - minY);

    // TODO: Interpolate the perlinNoise
    // Get height of the world floor for the specific segment
    int height = worldHeight / 2 - perlinNoise[(x / 255) % 2].perlinNoise(x - (255 * (x / 255)));

    // switch to next chunk and make a new perlin noise
    if(worldSeed + int(x / 255) != perlinNoise[(x / 255) % 2].getSeed()) {
        perlinNoise[(x / 255) % 2] = RandomTerrain(worldSeed + int(x / 255), 255);
    }

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