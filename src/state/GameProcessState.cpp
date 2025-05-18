#include "../../include/state/GameProcessState.hpp"

#include <filesystem>
#include <string>
#include <iostream>
#include "../../include/constants/path.h"
#include "../../include/constants/main_constants.h"
#include "../../include/Game.hpp"

namespace fs = std::filesystem;

GameProcessState::GameProcessState() {
    infoLog("GameProcessState::GameProcessState", "Вызван конструктор");
}

void GameProcessState::loadRooms() {
    std::string levelsFolder = LEVEL_PATH;
    std::string targetExt = ".tmx";

    try {
        // Проверка существования директории с уровнями
        if (!fs::exists(levelsFolder)) {
            errorLog("GameProcessState::loadRooms", "Директория с уровнями не существует: " + levelsFolder);
            throw std::runtime_error("Levels directory does not exist");
        }

        // Перебор всех папок в levelsFolder
        for (const auto& levelFolder : fs::directory_iterator(levelsFolder)) {
            if (!levelFolder.is_directory()) continue;

            // Перебор всех папок в levelFolder
            for (const auto& roomFolder : fs::directory_iterator(levelFolder)) {
                if (!roomFolder.is_directory()) continue;

                // Перебор всех файлов в roomFolder
                for (const auto& file : fs::directory_iterator(roomFolder)) {
                    if (!file.is_regular_file()) continue;

                    if (file.path().extension().string() == targetExt) {
                        infoLog("GameProcessState::loadRooms", "Загружается файл: " + file.path().string());
                        rooms.push_back(std::make_unique<Room>(Game::getInstance().getTextureManager(), file.path().string()));
                        break;
                    }
                }
            }            
        }
    } catch (const fs::filesystem_error& e) {
        errorLog("GameProcessState::loadRooms", "Ошибка при чтении файлов: " + std::string(e.what()));
        throw;
    }
}

void GameProcessState::setCurrentRoomIndex(int newIndex) {
    if (newIndex < 0 || newIndex >= rooms.size()) {
        errorLog("GameProcessState::setCurrentRoomIndex", "Индекс вне диапазона");
        return;
    }
    currentRoomIndex = newIndex;
}

void GameProcessState::handleInput(const sf::Event& event) {
    if (rooms.empty()) return;
    
    PlayerUIState& playerUIState = PlayerUIState::getInstance();

    playerUIState.handleInput(event);

    if (auto keyEvent = event.getIf<sf::Event::KeyPressed>()) {
        if (auto* camera = Game::getInstance().getCamera()) {
            camera->handleInput(keyEvent);
        }

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
}

void GameProcessState::onEnter() {
    Game& gameInstance = Game::getInstance();

    try {
        player = std::make_unique<Player>(gameInstance.getTextureManager());
        if (!player) {
            errorLog("GameProcessState::onEnter", "Не удалось создать игрока");
            throw std::runtime_error("Failed to create player");
        }

        loadRooms();
        
        // Проверяем, что комнаты загружены
        if (rooms.empty()) {
            errorLog("GameProcessState::onEnter", "Не удалось загрузить комнаты");
            throw std::runtime_error("Failed to load rooms");
        }

        // Устанавливаем начальный индекс комнаты
        currentRoomIndex = 0;
        infoLog("GameProcessState::onEnter", "Установлен начальный индекс комнаты: " + std::to_string(currentRoomIndex));
        
        // Устанавливаем начальную позицию камеры на игрока
        if (auto* camera = gameInstance.getCamera()) {
            sf::Vector2f playerPos = player->getPosition();
            sf::Vector2f pixelPos = {playerPos.x * TILE_SIZE, playerPos.y * TILE_SIZE};
            camera->setCenter(pixelPos);
        } else {
            errorLog("GameProcessState::onEnter", "Камера не найдена");
        }

        
        PlayerUIState::getInstance().onEnter();

    } catch (const std::exception& e) {
        errorLog("GameProcessState::onEnter", "Ошибка при инициализации: " + std::string(e.what()));
        throw;
    }
}

void GameProcessState::onExit() {
    infoLog("GameProcessState::onExit", "Вызван метод onExit");

    PlayerUIState::getInstance().onExit();
}

void GameProcessState::render(sf::RenderWindow& window) {
    if (rooms.empty()) {
        errorLog("GameProcessState::render", "Вектор комнат пуст");
        return;
    }
    
    if (currentRoomIndex >= rooms.size()) {
        errorLog("GameProcessState::render", "Индекс текущей комнаты вне диапазона: " + 
            std::to_string(currentRoomIndex) + " >= " + std::to_string(rooms.size()));
        return;
    }

    rooms[currentRoomIndex]->render(window);
    window.draw(*player);

    PlayerUIState::getInstance().render(window);
}
