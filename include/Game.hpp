#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "../include/state/GameProcessState.hpp"

/**
 * Класс Game представляет собой основную игровую логику и управление игровым процессом.
 * Он отвечает за создание окна игры, загрузку ресурсов и управление состоянием игры.
 * Он использует менеджер ресурсов для загрузки текстур и управления ими.
 */

class Game {
private:
    // Окно игры
    sf::RenderWindow window;
    // Менеджер текстур служит для загрузки тайлсета из файловой системы
    ResourceManager<sf::Texture> textureManager;
    // Указатель на cостояние игрового процесса
    std::unique_ptr<GameProcessState> gameProcessState;
public:
    Game();

    // Метод для запуска игры
    void run();
};