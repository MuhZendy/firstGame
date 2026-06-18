#pragma once
#include "raylib.h"

struct AssetManager {
    Texture2D texture = {};
    Texture2D frame = {};
    void loadAll();
};