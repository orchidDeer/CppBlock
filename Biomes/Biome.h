#ifndef CPPBLOCK_BIOME_H
#define CPPBLOCK_BIOME_H

#include <random>

/**
 * View of an X coordinate and terrain height for a X coordinate.
 */
struct Segment {
    /// View matrix
    std::vector<short int> data;

    /// Terrain height
    int height;
};

class Biome {
public:
    virtual ~Biome() = default;

    /**
     * Generates a segment and gives the view matrix of the segment back and the terrain height
     * @param x Position in Chunk
     * @param minY The minimal Y position for the view matrix
     * @param maxY The maximal Y position for the view matrix
     * @param height World height
     * @param chunkSize Size of the Chunk
     * @return When minY and maxY are 0 only the terrain height gets returned
     *         else the terrain height and view matrix get returned.
     */
    virtual Segment generateSegmentView(int x, int &minY, int &maxY, int &height, int chunkSize) = 0;

    /**
     * Returns the Biome seed.
     * @return Biome seed
     */
    int getSeed();

    /**
     * Interpolates between two heights
     * @param h0 Height one
     * @param h1 Height two
     * @param w Bias
     * @return Interpolated height
     */
    static int interpolate(int h0, int h1, float w);

protected:
    /**
     * Create matrix.
     * @param height Terrain height.
     * @param minY The minimal Y position for the view matrix
     * @param maxY The maximal Y position for the view matrix
     * @return View matrix for segment.
     */
    static std::vector<short int> terrain(int &height, int &minY, int &maxY);

    /// Biome seed
    int seed = 0;
};

#endif //CPPBLOCK_BIOME_H
