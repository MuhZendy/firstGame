#pragma once
#include "raylib.h"

struct AssetManager {
    Texture2D texture = {};
    Texture2D frame = {};
    Texture2D treeTexture = {};
    void loadAll();
};