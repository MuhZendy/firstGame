#include <vector>
#include <fstream>
#include "blocks.h"

bool saveBlockDataToFile(std::vector<Block> blocks, int w, int h, const char* filename);
bool loadBlockDataFromFile(std::vector<Block>& blocks, int& w, int& h, const char filename);