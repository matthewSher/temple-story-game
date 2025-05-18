#include "../include/Game.hpp"

#include <memory>
#include "../include/tools/TileMap.hpp"
#include "../include/state/GameProcessState.hpp"
#include "../include/state/MenuState.hpp"
#include "../include/constants/path.h"
#include "../include/constants/main_constants.h"

Game::Game() {
    infoLog("Game::Game", "Вызван конструктор");
    window = sf::RenderWindow(sf::VideoMode({GameSettings::WINDOW_WIDTH, GameSettings::WINDOW_HEIGHT}), "Game");
    window.setFramerateLimit(GameSettings::FPS_LIMIT);
    
    // Загрузка ресурсов
    if (!textureManager.load("tileset", TILESET_PATH)) {
        throw std::runtime_error("Error loading tileset");
    }
    if (!fontManager.load("regular", REGULAR_FONT_PATH) || !fontManager.load("bold", BOLD_FONT_PATH)) {
        throw std::runtime_error("Error loading font");
    }
    
    camera = std::make_unique<Camera>(window);
    // Не создаём MenuState здесь!
}

void Game::init() {
    pushState(std::make_unique<MenuState>());
}

void Game::run() {
    while (window.isOpen()) {
        render();
        handleEvents();
        update();
    }
}

ResourceManager<sf::Texture>& Game::getTextureManager() { 
    return textureManager; 
}

ResourceManager<sf::Font>& Game::getFontManager() { 
    return fontManager; 
}

Camera* Game::getCamera() { 
    return camera.get(); 
}

sf::RenderWindow& Game::getWindow() { 
    return window; 
}

void Game::handleEvents() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
            return;
        }
        
        if (stateManager.isStateValid()) {
            stateManager.handleInput(*event);
        }
    }
}

void Game::update() {
    if (camera) {
        camera->apply(window);
    }
}

void Game::render() {
    window.clear();
    stateManager.renderCurrent(window);
    window.display();
}

void Game::pushState(std::unique_ptr<GameState> state) {
        stateManager.push(std::move(state));
}
    
void Game::popState() {
    stateManager.pop();
}

void Game::changeState(std::unique_ptr<GameState> state) {
    stateManager.change(std::move(state));
}

Game& Game::getInstance() {
    static Game instance; // Создаём единственный экземпляр класса
    return instance;
}
