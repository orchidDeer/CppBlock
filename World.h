#ifndef CMINECRAFT_WORLD_H
#define CMINECRAFT_WORLD_H

#include <vector>
#include <iostream>
#include "RandomTerrain.h"

/**
 * Infinite world.
 */
class World {
public:
    /**
     * Create infinite world based on seed.
     * @param height Max world height.
     * @param seed Seed on which World gets generated.
     */
    World(int height, int seed);
    ~World();

    /**
     * Edits the world that was created by the seed.
     */
    void edit();

    /**
     * The terrain height.
     * @param x X position
     * @return The terrain height at the x position.
     */
    int getTerrainHeight(int x);

    /**
     * Generates next segment.
     * @param x X position of segment.
     * @param maxY Upper bound of vector.
     * @param minY Lower bound of vector.
     * @return Vector of world segment in Y range of minY and maxY.
     */
    std::vector<short int> createNext(int x, int maxY, int minY);

private:
    /// Perlin noise to generate base world
    RandomTerrain perlinNoise[2] = { RandomTerrain(0, 119),
                                   RandomTerrain(0, 119) };
    /// Total height of world.
    int worldHeight;

    /// World seed
    int worldSeed;

    // Area posX posY change
    //std::vector<std::vector<std::vector<short int>>> change;
};

#endif //CMINECRAFT_WORLD_H
