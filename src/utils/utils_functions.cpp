#include "../../include/utils/utils_functions.h"

#include "../../include/constants/main_constants.h"

sf::Vector2i getTileCoordsById(int id) {
    // Вычисление позиции тайла (в тайлах)
    int tu = id % TILE_COUNT_IN_ONE_ROW;
    int tv = id / TILE_COUNT_IN_ONE_ROW;
    
    // Вычисление позиции тайла (в пикселях)
    int tileX = tu * (TILE_SIZE + OFFSET_BETWEEN_TILES) + OFFSET_BETWEEN_TILES;
    int tileY = tv * (TILE_SIZE + OFFSET_BETWEEN_TILES) + OFFSET_BETWEEN_TILES;

    return {tileX, tileY};
}