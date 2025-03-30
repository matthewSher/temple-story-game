#pragma once

// #include <memory>
#include "GameState.hpp"
#include "../entities/Player.hpp"

class GameProcessState : public GameState {
private:
    std::unique_ptr<Player> player;
    ResourceManager<sf::Texture, TextureKeys> textureManager;

public:
    GameProcessState(ResourceManager<sf::Texture, TextureKeys>& textureManager);

    void handleInput(const sf::Event::KeyPressed *keyEvent) override;
    void render(sf::RenderWindow& window) override;
};