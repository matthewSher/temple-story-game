#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include "../include/Game.hpp"

int main() {
    // Установка кодовой страницы UTF-8 для консоли Windows
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    Game& game = Game::getInstance();
    game.init();
    game.run();

    return 0;
}