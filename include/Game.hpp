#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "constants/TextureKeys.hpp"
#include "../include/state/GameProcessState.hpp"

/**
 * Основной класс. Требуется для запуска игры, создания окна и
 * его настройки.
 */

class Game {
private:
    // Окно игры
    sf::RenderWindow window;
    // Менеджер текстур служит для загрузки тайлсета из файловой системы
    ResourceManager<sf::Texture, TextureKeys> textureManager;
    std::unique_ptr<GameProcessState> gameProcessState;
public:
    Game();

    // Метод для запуска игры
    void run();
};