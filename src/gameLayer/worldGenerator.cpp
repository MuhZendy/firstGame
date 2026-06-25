#include <FastNoise/FastNoise.h>
#include "worldGenerator.h"
#include "randomStuff.h"

static float lerp(float a, float b, float t) {
    return a + (b - a) * t;
}

static void adjustNoise(float& noise, float power) {
    noise = (noise + 1) / 2;
    noise = std::pow(noise, power);
}

void generateWorld(GameMap& gameMap, int seed) {
    int width = gameMap.width;
    int height = gameMap.height;

    std::ranlux24_base rng(seed++); // Random number generator

    auto planeNoise = FastNoise::New<FastNoise::Perlin>();
    auto mountainNoise = FastNoise::New<FastNoise::Perlin>();
    auto planeMountainMixer = FastNoise::New<FastNoise::Perlin>();

    int dirtOffsetStart = -5;
    int dirstOffsetEnd = 10;

    int stoneHeightStart = height / 4;
    int stoneHeightEnd = height;

    // Example: Fill the bottom half with dirt and the top half with air
    for (int x = 0; x < width; ++x) {

        float fMountainComponent = mountainNoise->GenSingle2D(x, 0, seed);
        adjustNoise(fMountainComponent, 3);

        float fPlaneComponent = planeNoise->GenSingle2D(x, 0, seed+1);
        adjustNoise(fPlaneComponent, 1);

        float fPlaneMountainMix = planeMountainMixer->GenSingle2D(x, 0, seed+2);
        adjustNoise(fPlaneMountainMix, 1);

        float stoneNoise = lerp(fPlaneComponent, fMountainComponent, fPlaneMountainMix);
        float dirtNoise = 0.5f;

        int stoneHeight = lerp(stoneHeightStart, stoneHeightEnd, stoneNoise);
        int dirtOffset = lerp(dirtOffsetStart, dirstOffsetEnd, dirtNoise);
        int dirtHeight = stoneHeight - dirtOffset;

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