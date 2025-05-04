#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "../include/state/GameProcessState.hpp"
#include "../include/tools/Camera.hpp"
#include "../include/constants/game_settings.hpp"
#include "tools/ResourceManager_T.hpp"
#include "state/StateManager.hpp"

/**
 * Класс Game представляет собой основную игровую логику и управление игровым процессом.
 * Он отвечает за создание окна игры, загрузку ресурсов и управление состоянием игры.
 * Он использует менеджеры ресурсов для загрузки текстур и шрифтов.
 * Он использует менеджер состояний для управления состояниями игры.
 */
class Game {
private:
    // Окно игры
    sf::RenderWindow window;
    // Менеджер текстур служит для загрузки тайлсета из файловой системы
    ResourceManager<sf::Texture> textureManager;
    // Менеджер шрифтов служит для загрузки шрифтов из файловой системы
    ResourceManager<sf::Font> fontManager;
    // Указатель на камеру
    std::unique_ptr<Camera> camera;
    // Менеджер состояний служит для управления состояниями игры
    StateManager stateManager;

    // Метод для обработки событий
    void handleEvents();
    // Метод для обновления состояния игры
    void update();
    // Метод для отрисовки состояния игры
    void render();

public:
    Game();

    // Метод для запуска игры
    void run();
    
    // Геттеры для доступа к ресурсам
    ResourceManager<sf::Texture>& getTextureManager() { return textureManager; }
    ResourceManager<sf::Font>& getFontManager() { return fontManager; }
    Camera* getCamera() { return camera.get(); }
    sf::RenderWindow& getWindow() { return window; }
    
    // Метод для закрытия окна
    void closeWindow() { window.close(); }
    
    // Методы для работы с состояниями
    void pushState(std::unique_ptr<GameState> state);
    void popState();
    void changeState(std::unique_ptr<GameState> state);
};