#pragma once

#include "Character.hpp"
#include "../tools/ResourceManager_T.hpp"
#include "../constants/TextureKeys.hpp"

class Player : public Character {
private:
    sf::Sprite createSprite(ResourceManager<sf::Texture, TextureKeys>& textureManager);

public:
    Player(ResourceManager<sf::Texture, TextureKeys>& textureManager);
};