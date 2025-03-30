#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "constants/TextureKeys.hpp"
#include "state/GameState.hpp"
#include "tools/ResourceManager_T.hpp"
#include "../include/entities/Player.hpp"
#include "../include/state/GameProcessState.hpp"

/**
 * Основной класс. Требуется для запуска игры, создания окна и
 * его настройки.
 */

class GameProcessState;

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