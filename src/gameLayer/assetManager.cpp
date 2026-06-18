#include "assetManager.h"

void AssetManager::loadAll() {
    texture = LoadTexture(RESOURCES_PATH "textures.png");
    frame = LoadTexture(RESOURCES_PATH "frame.png");
    treeTexture = LoadTexture(RESOURCES_PATH "treetextures.png");
}