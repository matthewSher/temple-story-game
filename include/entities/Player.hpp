#pragma once

#include "Character.hpp"
#include "../tools/ResourceManager_T.hpp"

class Player : public Character {
private:
    sf::Sprite createSprite(ResourceManager<sf::Texture>& textureManager);

public:
    Player(ResourceManager<sf::Texture>& textureManager);
};