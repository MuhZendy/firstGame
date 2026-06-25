#include <FastNoise/FastNoise.h>
#include "worldGenerator.h"
#include "randomStuff.h"

void generateWorld(GameMap& gameMap, int seed) {
    int width = gameMap.width;
    int height = gameMap.height;

    int dirtHeight = height / 4; // Example: Half the height is dirt

    std::ranlux24_base rng(seed++); // Random number generator

    auto dirtNoise = FastNoise::New<FastNoise::Perlin>();
    auto stoneNoise = FastNoise::New<FastNoise::Perlin>();

    int previousHeight = dirtHeight; // Start with the initial dirt height

    // Example: Fill the bottom half with dirt and the top half with air
    for (int x = 0; x < width; ++x) {

        float fDirtHeight = dirtNoise->GenSingle2D(x, 0, seed);
        int dirtHeight = fDirtHeight * 20 + 20;

        float fStoneHeight = dirtNoise->GenSingle2D(x, 0, seed+1);
        int stoneHeight = fStoneHeight * 20 + 30;

        for (int y = 0; y < height; ++y) {
            if (y == dirtHeight) {
                gameMap.getBlock(x, y).id = Block::grassBlock; // Grass block at the surface
            } else if (y > dirtHeight && y <= stoneHeight) {
                gameMap.getBlock(x, y).id = Block::dirt;
            } else if (y > stoneHeight) {
                gameMap.getBlock(x, y).id = Block::stone;
            }
        }
    }
}