#include "World.h"

#define CHUNKSIZE 500

World::World(int height, int seed) : distribution(0, 100), chunkDistribution(0, 1) {
    this->worldHeight = height;
    this->worldSeed = seed;

    // currentBiome needs to point to a biome
    currentBiome = std::move(std::make_unique<Plains>(0, distribution, dre));
}

World::~World() {
    //change.clear();
}

Segment World::getSegment(int x, int minY, int maxY) {

    // Check if currentBiome has the right biome seed
    if(currentBiome->getSeed() != worldSeed + int(x / CHUNKSIZE)) {
        dre.seed(worldSeed + int(x / CHUNKSIZE) - 1421);

        // Choose a random biome type and point to it
        switch (chunkDistribution(dre)) {
            case 0:
                currentBiome = std::move(std::make_unique<MountainBiome>(worldSeed + int(x / CHUNKSIZE),
                                                                                distribution, dre));
                break;
            case 1:
                currentBiome = std::move(std::make_unique<Plains>(worldSeed + int(x / CHUNKSIZE),
                                                                         distribution, dre));
                break;
        }
    }

    // Get segment information
    Segment segment = currentBiome->generateSegmentView(x - int(x / CHUNKSIZE) * CHUNKSIZE, minY, maxY,
                                                        worldHeight, CHUNKSIZE);

    return segment;
}
