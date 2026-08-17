#include "saveMap.h"
#include "asserts.h"

bool saveBlockDataToFile(std::vector<Block> blocks, int w, int h, const char* filename) {
    std::ofstream file(filename, std::ios::binary);

    if (!file.is_open()) { return false; }

    permaAssertCommentDevelopement(blocks.size() == w*h);
    permaAssertCommentDevelopement(blocks.size() != 0);

    file.write((const char*) w, sizeof(w));
    file.write((const char*) h, sizeof(h));
    file.write((const char*) blocks.data(), sizeof(Block) * blocks.size());

    file.close();

    return true;
}

bool loadBlockDataFromFile(std::vector<Block>& blocks, int& w, int& h, const char* filename) {
    blocks.clear();
    w = 0;
    h = 0;

    std::ifstream file(filename, std::ios::binary);

    file.read((char*) &w, sizeof(w));
    file.read((char*) &h, sizeof(h));

    if (!file || w == 0 || h == 0 || w > 10000 || h > 10000) {
        file.close();
        return false;
    }

    int blockCount = w * h;
    file.read((char*) blocks.data(), sizeof(Block) * blockCount);

    if (!file) {
        blocks.clear();
        w = 0;
        h = 0;
        file.close();
        return false;
    }

    for (int i = 0; i < blocks.size(); i++) {
        blocks[i].sanitize();
    }

    file.close();
    return true;
}