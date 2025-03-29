#pragma once

#include <memory>
#include "GameState.hpp"
#include "../entities/Player.hpp"

class GameProcessState : public GameState {
private:
    Player player;
    ResourceManager<sf::Texture>& textureManager;

    Player createPlayer();

public:
    GameProcessState(ResourceManager<sf::Texture>& textureManager);

    void handleInput(const std::optional<sf::Event>& event) override;
    void render(sf::RenderWindow& window) override;
};