#ifndef CPPBLOCK_MOUNTAINBIOME_H
#define CPPBLOCK_MOUNTAINBIOME_H

#include "Biome.h"
#include "../PerlinNoise.h"

/**
 * Mountain biome.
 */
class MountainBiome : public Biome{
public:
    /**
     * Generates random frequency and amplitudes for terrain generation.
     * @param seed Random Biome seed
     * @param distribution Distribution between 0 and 100
     * @param dre Random engine
     */
    MountainBiome(int seed, std::uniform_int_distribution<int> &distribution,
                  std::default_random_engine &dre);
    ~MountainBiome() override;

    Segment generateSegmentView(int x, int &minY, int &maxY, int &height, int chunkSize) override;

private:
    /// Stores random amplitude
    float amplitude[8]{};
    /// Stores random frequency
    float frequency[8]{};

    /// Perlin noise for generating terrain
    PerlinNoise perlinNoise;
};

#endif //CPPBLOCK_MOUNTAINBIOME_H