#include "Biome.h"

std::vector<short int> Biome::terrain(int &height, int &minY, int &maxY) {
    std::vector<short int> data;
    data.resize(std::abs(maxY - minY));

    // Write data to world segment
    for (int i = minY; i < maxY; ++i) {
        if(i > height) {
            data[i - minY] = 0;
        } else {
            data[i - minY] = 1;
        }
    }

    return data;
}

int Biome::getSeed() {
    return seed;
}

int Biome::interpolate(int h0, int h1, float w) {
    // Clips ends
    if (0.04f > w)
        return h1;
    else if (0.95f < w)
        return h0;

    // Interpolation
    return std::ceil(float(h0 - h1) * ((w * (w * 6.f - 15.f) + 10.f) * w * w * w) + float(h1));
}