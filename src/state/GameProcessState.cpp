#include "../../include/state/GameProcessState.hpp"

#include <filesystem>
#include <string>
#include <iostream>
#include "../../include/constants/path.h"

namespace fs = std::filesystem;

GameProcessState::GameProcessState(ResourceManager<sf::Texture>& textureManager)
    : textureManager(textureManager) {
    infoLog("GameProcessState::GameProcessState", "Вызван конструктор");
    player = std::make_unique<Player>(textureManager);
    loadRooms();
}

void GameProcessState::loadRooms() {
    std::string levelsFolder = LEVEL_PATH;
    std::string targetExt = ".tmx";

    try {
        // Перебор всех папок в levelsFolder
        for (const auto& levelFolder : fs::directory_iterator(levelsFolder)) {
            if (!levelFolder.is_directory()) continue;

            // Перебор всех папок в levelFolder
            for (const auto& roomFolder : fs::directory_iterator(levelFolder)) {
                if (!roomFolder.is_directory()) continue;

                // Перебор всех файлов в roomFolder
                for (const auto& file : fs::directory_iterator(roomFolder)) {
                    if (!file.is_regular_file()) continue;

                    // Если файл имеет нужное расширение, загружаем его
                    if (file.path().extension().string() == targetExt) {
                        infoLog("GameProcessState::loadRooms", "Загружается файл: " + file.path().string());
                        std::string fileExt = levelFolder.path().extension().string();
                        
                        rooms.push_back(std::make_unique<Room>(textureManager, file.path().string()));
                    }
                }
            }            
        }
    } catch (const fs::filesystem_error& e) {
        errorLog("GameProcessState::loadRooms", "Ошибка при чтении файлов");
    }
}

void GameProcessState::setCurrentRoomIndex(int newIndex) {
    if (newIndex < 0 || newIndex >= rooms.size()) {
        errorLog("GameProcessState::setCurrentRoomIndex", "Индекс вне диапазона");
        return;
    }
    currentRoomIndex = newIndex;
}

void GameProcessState::handleInput(const sf::Event::KeyPressed *keyEvent) {
    switch (keyEvent->code) {
    case sf::Keyboard::Key::A:
        if (!rooms[currentRoomIndex]->checkCollision(player->getPosition() + sf::Vector2f(-1, 0))) {
            player->move({-1, 0});
        }
        break;
    case sf::Keyboard::Key::D:
        if (!rooms[currentRoomIndex]->checkCollision(player->getPosition() + sf::Vector2f(1, 0))) {
            player->move({1, 0});
        }
        break;
    case sf::Keyboard::Key::W:
        if (!rooms[currentRoomIndex]->checkCollision(player->getPosition() + sf::Vector2f(0, -1))) {
            player->move({0, -1});
        }
        break;
    case sf::Keyboard::Key::S:
        if (!rooms[currentRoomIndex]->checkCollision(player->getPosition() + sf::Vector2f(0, 1))) {
            player->move({0, 1});
        }
        break;
    case sf::Keyboard::Key::E:
        rooms[currentRoomIndex]->interactWithStaticObjectAt(player->getPosition());
        break;
    default:
        break;
    }
}

void GameProcessState::render(sf::RenderWindow& window) {
    rooms[currentRoomIndex]->render(window);
    window.draw(*player);
}