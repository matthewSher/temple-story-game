#pragma once

#include <string>

/**
 * В файле определены основные локальные пути, используемые в проекте.
 * Эти пути указывают на различные ресурсы (например, текстуры, карты тайлов и т.д.),
 * которые используются в игре.
 */

const std::string TILESET_PATH = "..\\..\\assets\\tileset\\tileset.png";          // Путь к текстурам
const std::string REGULAR_FONT_PATH = "..\\..\\assets\\fonts\\EpilepsySans.ttf";  // Путь к шрифту
const std::string BOLD_FONT_PATH = "..\\..\\assets\\fonts\\EpilepsySansBold.ttf"; // Путь к жирному шрифту
const std::string LEVEL_PATH = "..\\..\\assets\\levels\\";                        // Путь к уровням
const std::string STATIC_OBJECTS_CONFIG_FILENAME = "static_objects.json";  // Путь к конфигурации статичных объектов