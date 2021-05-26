#ifndef CPPBLOCK_PLAINS_H
#define CPPBLOCK_PLAINS_H

#include "Biome.h"
#include "../PerlinNoise.h"

/**
 * Plains biome.
 */
class Plains : public Biome {
public:
    /**
     * Generates random frequency and amplitudes for terrain generation.
     * @param seed Random Biome seed
     * @param distribution Distribution between 0 and 100
     * @param dre Random engine
     */
    Plains(int seed, std::uniform_int_distribution<int> &distribution,
                  std::default_random_engine &dre);
    ~Plains() override;

    Segment generateSegmentView(int x, int &minY, int &maxY, int &height, int chunkSize) override;

private:
    /// Stores random amplitude
    float amplitude[3]{};
    /// Stores random frequency
    float frequency[3]{};

    /// Perlin noise for generating terrain
    PerlinNoise perlinNoise;
};

#endif //CPPBLOCK_PLAINS_H
