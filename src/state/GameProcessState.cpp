#include "../../include/state/GameProcessState.hpp"

#include <filesystem>
#include <string>

namespace fs = std::filesystem;

GameProcessState::GameProcessState(ResourceManager<sf::Texture, TextureKeys>& textureManager)
    : textureManager(textureManager) {
    infoLog("GameProcessState::GameProcessState", "Вызван конструктор");
    player = std::make_unique<Player>(textureManager);
    loadRooms();
}

void GameProcessState::loadRooms() {
    std::string locationsFolder = "./assets/locations/";
    std::string targetExt = ".tmx";

    try {
        for (const auto& folderItem : fs::directory_iterator(locationsFolder)) {
            if (!folderItem.is_regular_file()) continue;

            std::string fileExt = folderItem.path().extension().string();
            if (fileExt == targetExt) {
                rooms.push_back(std::make_unique<Room>(textureManager, folderItem.path().string()));
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
        player->move({-1, 0});
        break;
    case sf::Keyboard::Key::D:
        player->move({1, 0});
        break;
    case sf::Keyboard::Key::W:
        player->move({0, -1});
        break;
    case sf::Keyboard::Key::S:
        player->move({0, 1});
        break;
    default:
        break;
    }
}

void GameProcessState::render(sf::RenderWindow& window) {
    rooms[currentRoomIndex]->render(window);
    window.draw(*player);
}