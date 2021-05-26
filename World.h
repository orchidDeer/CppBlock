#ifndef CMINECRAFT_WORLD_H
#define CMINECRAFT_WORLD_H

#include <vector>
#include <iostream>
#include <memory>
#include "Biomes/Biome.h"
#include "Biomes/MountainBiome.h"
#include "Biomes/Plains.h"

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
     * Generates next segment.
     * @param x X position of segment.
     * @param maxY Upper bound of vector.
     * @param minY Lower bound of vector.
     * @return Vector of world segment in Y range of minY and maxY.
     */
    Segment getSegment(int x, int maxY, int minY);

private:
    /// Unique pointer that points on the current Biome
    std::unique_ptr<Biome> currentBiome;
    /// Distribution for Biome generation
    std::uniform_int_distribution<int> distribution;
    /// Distribution for picking a Biome
    std::uniform_int_distribution<int> chunkDistribution;
    /// Random engine
    std::default_random_engine dre;

    /// Total height of world.
    int worldHeight;

    /// World seed
    int worldSeed;

    // Area posX posY change
    //std::vector<std::vector<std::vector<short int>>> change;
};

#endif //CMINECRAFT_WORLD_H
