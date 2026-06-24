#pragma once
#include <random>

float getRandomFloat(std::ranlux24_base& rng, float min, float max);
int getRandomInt(std::ranlux24_base& rng, int min, int max);
bool getRandomBool(std::ranlux24_base& rng, float probability = 0.5f);