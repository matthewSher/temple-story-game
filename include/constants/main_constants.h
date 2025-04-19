#pragma once

/**
 * Основные константы, используемые в коде игры.
 * Эти константы определяют различные параметры игры, такие как размеры тайлов,
 * количество вершин в тайле и другие настройки.
 */

/**
 * Константы, касающиеся параметров тайла и основного тайлсета
 */
const int TILE_SIZE = 12; // Размер тайла в пикселях
const int VERTECES_IN_TILE = 6; // Количество вершин в одном тайле (двойной треугольник)
const int TILE_COUNT_IN_ONE_ROW = 103; // Количество тайлов в одной строке тайлсета
const int OFFSET_BETWEEN_TILES = 1; // Отступ между тайлами в тайлсете