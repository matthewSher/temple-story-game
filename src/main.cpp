#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include "../include/Game.hpp"

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    Game game;
    game.run();

    return 0;
}