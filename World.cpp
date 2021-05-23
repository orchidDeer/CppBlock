#include "World.h"

World::World(int height, int seed) {
    this->worldHeight = height;

    perlinNoise[0] = RandomTerrain(seed, 119);
    perlinNoise[1] = RandomTerrain(seed + 1, 119);
}

World::~World() {
    //change.clear();
}

int World::getTerrainHeight(int x) {
    return worldHeight / 2 - perlinNoise[0].perlinNoise(x);
}

std::vector<short int> World::createNext(int x, int maxY, int minY) {
    // Vector of world segment
    std::vector<short int> line;
    // Resize vector to fit the requested range
    line.resize(maxY - minY);

    // TODO: Generate from new RandomTerrain when old one is out of bound
    // Get height of the world floor for the specific segment
    int height = worldHeight / 2 - perlinNoise[0].perlinNoise(x);

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