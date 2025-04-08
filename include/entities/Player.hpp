#pragma once

#include "Character.hpp"
#include "../tools/ResourceManager_T.hpp"
#include "../constants/TextureKeys.hpp"

/**
 * Класс Player представляет собой игрового персонажа, управляемого игроком.
 * Он наследуется от класса Character и добавляет функциональность
 * для управления состоянием игрока, его движением и взаимодействием с окружающим миром.
 */
class Player : public Character {
private:
    // Метод для создания спрайта игрока, используя менеджер ресурсов
    sf::Sprite createSprite(ResourceManager<sf::Texture, TextureKeys>& textureManager);

public:
    Player(ResourceManager<sf::Texture, TextureKeys>& textureManager);
};