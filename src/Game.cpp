#include "../include/Game.hpp"

#include <memory>
#include "../include/tools/TileMap.hpp"
#include "../include/state/GameProcessState.hpp"
#include "../include/constants/path.h"

Game::Game() {
    infoLog("Game::Game", "Вызван конструктор");

    window = sf::RenderWindow(sf::VideoMode({GameSettings::WINDOW_WIDTH, GameSettings::WINDOW_HEIGHT}), "Game");
    window.setFramerateLimit(GameSettings::FPS_LIMIT);

    // Загрузка тайлсета в буфер с ресурсами
    if (!textureManager.load("tileset", TILESET_PATH)) {
        errorLog("Game::Game", "Ошибка загрузки тайлсета");
        throw std::runtime_error("Error loading tileset");
    }

    gameProcessState = std::make_unique<GameProcessState>(textureManager);
    camera = std::make_unique<Camera>(window);
}

void Game::handleEvents() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
            return;
        }

        if (event->is<sf::Event::KeyPressed>()) {
            const auto* keyEvent = event->getIf<sf::Event::KeyPressed>();
            gameProcessState->handleInput(keyEvent);
            camera->handleInput(keyEvent);
        }
    }
}

void Game::update() {
    camera->apply(window);
}

void Game::render() {
    window.clear();
    gameProcessState->render(window);
    window.display();
}

void Game::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}