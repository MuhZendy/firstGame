#include <FastNoise/FastNoise.h>
#include <vector>
#include <iostream>
#include "worldGenerator.h"
#include "randomStuff.h"

static auto source = FastNoise::New<FastNoise::Simplex>();
static auto fractal = FastNoise::New<FastNoise::FractalFBm>();
static auto cellular = FastNoise::New<FastNoise::CellularLookup>();
static int width, height;
static int worldMinHeight, worldMaxHeight;

static float lerp(float a, float b, float t) {
    return a + (b - a) * t;
}

static void setupNoiseGenerator() {
    source->SetOutputMin(0.f);
    source->SetOutputMax(0.57f);

    fractal->SetSource(source);
    fractal->SetGain(0.5f);
    fractal->SetWeightedStrength(0.f);
    fractal->SetOctaveCount(3);
    fractal->SetLacunarity(2.f);

    cellular->SetLookup(source);
    cellular->SetMinkowskiP(1.5f);
    cellular->SetGridJitter(1.f);
    cellular->SetSizeJitter(0.f);
    cellular->SetSeedOffset(1337);
}

static void generateWorldOutline(int* worldOutline, int seed) {

    float heightNoise[width], heightNoiseSmooth[width], noiseMix[width];

    fractal->GenUniformGrid2D(heightNoise, 0.f, 0.f, width, 1, 1.f, 1.f, seed);
    fractal->GenUniformGrid2D(heightNoiseSmooth, 0.f, 0.f, width, 1, 0.1f, 0.1f, seed+1);
    fractal->GenUniformGrid2D(noiseMix, 0.f, 0.f, width, 1, 0.1f, 0.1f, seed+2);

    for (int x = 0; x < width; x++) {
        float noiseMult = lerp(heightNoise[x], heightNoiseSmooth[x], noiseMix[x]);
        worldOutline[x] = lerp(worldMinHeight, worldMaxHeight, noiseMult);
        // std::cout << noiseMult << ' ' << worldMinHeight << ' ' << worldMaxHeight << ' ' << worldOutline[x] << ';';
    }
    // std::cout << std::endl;
}

static void addStoneLayer(GameMap& gameMap, int* worldOutline) {
    for (int x = 0; x < width; x++) {
        for (int y = worldOutline[x]; y < worldMaxHeight; y++) {
            gameMap.getBlock(x, y).id = Block::stone;
        }
    }
}

static void addDirtLayer(GameMap& gameMap, int* worldOutline, int seed) {
    float offsetNoise[width];
    fractal->GenUniformGrid2D(offsetNoise, 0.f, 0.f, width, 1, 1.f, 1.f, seed+4);

    int minDirtOffset = -5;
    int maxDirtOffset = 10;

    for (int x = 0; x < width; x++) {
        int dirtHeight = worldOutline[x] - lerp(maxDirtOffset, minDirtOffset, offsetNoise[x]);
        for (int y = dirtHeight; y < worldOutline[x]; y++) {
            gameMap.getBlock(x, y).id = Block::dirt;
        }
    }
}

static void addDesertBiome(GameMap& gameMap, int seed) {
    float biomeNoise[width];
    cellular->GenUniformGrid2D(biomeNoise, 0.f, 0.f, width, 1, 1.f, 1.f, seed);

    for (int x = 0; x < width; x++) {
        if (biomeNoise[x] < 0.28f) continue;
        for (int y = 0; y < height; y++) {
            if (gameMap.getBlock(x, y).id == Block::dirt) {
                gameMap.getBlock(x, y).id = Block::sand;
            } else if (gameMap.getBlock(x, y).id == Block::stone) {
                gameMap.getBlock(x, y).id = Block::sandStone;
            }
        }
    }
}

static void addCaves(GameMap& gameMap, int seed) {
    float filter[width*height];
    source->GenUniformGrid2D(filter, 0.f, 0.f, width, height, 1.f, 1.f, seed+7331);

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (filter[y * width + x] < 0.1f) {
                gameMap.getBlock(x, y).id = Block::air;
            }
        }
    }
}

void generateWorld(GameMap& gameMap, int seed) {
    width = gameMap.width;
    height = gameMap.height;

    std::ranlux24_base rng(seed++); // Random number generator

    int worldOutline[width];
    worldMinHeight = height / 32;
    worldMaxHeight = height;

    setupNoiseGenerator();
    generateWorldOutline(worldOutline, seed);
    addStoneLayer(gameMap, worldOutline);
    addDirtLayer(gameMap, worldOutline, seed);
    addDesertBiome(gameMap, seed);
    addCaves(gameMap, seed);
}