#pragma once

#include <vector>
#include "GameState.hpp"
#include "../entities/Player.hpp"
#include "../env/Room.hpp"

class GameProcessState : public GameState {
private:
    std::unique_ptr<Player> player;
    ResourceManager<sf::Texture, TextureKeys> textureManager;
    std::vector<std::unique_ptr<Room>> rooms;
    int currentRoomIndex = 0;

    void loadRooms();

public:
    GameProcessState(ResourceManager<sf::Texture, TextureKeys>& textureManager);

    void setCurrentRoomIndex(int newIndex);

    void handleInput(const sf::Event::KeyPressed *keyEvent) override;
    void render(sf::RenderWindow& window) override;
};