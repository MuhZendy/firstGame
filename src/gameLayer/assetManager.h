#pragma once
#include "raylib.h"

struct AssetManager {
    Texture2D texture = {};
    void loadAll();
};