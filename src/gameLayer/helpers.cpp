#include "helpers.h"

Rectangle getTextureAtlasUV(int x, int y, int blockSizeX, int blockSizeY) {
    Rectangle uv;
    uv.width = (float)blockSizeX;
    uv.height = (float)blockSizeY;
    uv.x = (float)(x * blockSizeX);
    uv.y = (float)(y * blockSizeY);
    return uv;
}