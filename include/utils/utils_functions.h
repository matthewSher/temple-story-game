#pragma once

#include <SFML/Graphics.hpp>

/**
 * Функции-утилиты, упрощающие читаемость кода
 */

// Возвращает координаты тайла (в пикселях) из тайлсета. 
// Позиция прямоугольника определяется идентификатором
// (порядковым номером) тайла в тайлсете
sf::Vector2i getTileCoordsById(int id);