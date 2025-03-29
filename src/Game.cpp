#include "../include/Game.hpp"

#include <memory>
#include "../include/tools/TileMap.hpp"
#include "../include/state/GameProcessState.hpp"

Game::Game() {
    infoLog("Game::Game", "Вызван конструктор");

    window = sf::RenderWindow(sf::VideoMode({1280, 720}), "Game");

    // Загрузка тайлсета в буфер с ресурсами
    if (!textureManager.load("tileset", "assets/img/tileset.png")) {
        errorLog("Game::Game", "Ошибка загрузки тайлсета");
        return;
    }

    gameProcessState = std::make_unique<GameProcessState>(textureManager);
}

void Game::run() {
    sf::View view = window.getView();
    view.setSize(sf::Vector2f(window.getSize()) / 3.f);
    view.setCenter(sf::Vector2f(window.getSize()) / 2.f);
    window.setView(view);

    TileMap tileMap(textureManager.get("tileset"));
    if (!tileMap.load("assets/locations/1_part_map.tmx")) {
        errorLog("Game::run", "Ошибка загрузки тайлсета");
        return;
    }

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (event->is<sf::Event::KeyPressed>()) {
                float moveSpeed = 12.f;

                // Перемещение камеры с помощью стрелок
                const auto* keyEvent = event->getIf<sf::Event::KeyPressed>();

                // Управление персонажем
                gameProcessState->handleInput(keyEvent);

                switch (keyEvent->code) {
                case sf::Keyboard::Key::Left:
                    view.move({-moveSpeed, 0});
                    break;
                case sf::Keyboard::Key::Right:
                    view.move({moveSpeed, 0});
                    break;
                case sf::Keyboard::Key::Up:
                    view.move({0, -moveSpeed});
                    break;
                case sf::Keyboard::Key::Down:
                    view.move({0, moveSpeed});
                    break;
                default:
                    break;
                }

                window.setView(view);
            }
        }    

        window.clear();
        window.draw(tileMap);
        gameProcessState->render(window);
        window.display();
    }
}