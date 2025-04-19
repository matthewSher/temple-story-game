#pragma once

#include <vector>
#include "GameState.hpp"
#include "../entities/Player.hpp"
#include "../env/Room.hpp"

/**
 * Класс GameProcessState представляет собой состояние игрового процесса.
 * Он наследуется от класса GameState и отвечает за управление игровым процессом,
 * включая обработку ввода, отрисовку объектов и управление состоянием игры.
 * Он использует менеджер ресурсов для использования текстур.
 */
class GameProcessState : public GameState {
private:
    // Указатель на объект Player, представляющий игрока в игре
    std::unique_ptr<Player> player;
    // Менеджер ресурсов для загрузки текстур
    ResourceManager<sf::Texture> textureManager;
    // Вектор указателей на объекты Room, представляющие комнаты в игре
    std::vector<std::unique_ptr<Room>> rooms;
    // Индекс комнаты, в которой находится игрок
    int currentRoomIndex = 0;

    // Метод для загрузки текстур из файла
    void loadRooms();

public:
    GameProcessState(ResourceManager<sf::Texture>& textureManager);

    // Метод для установки текущего индекса комнаты
    void setCurrentRoomIndex(int newIndex);
    // Обработка ввода от игрока
    // keyEvent - событие нажатия клавиши, которое нужно обработать 
    void handleInput(const sf::Event::KeyPressed *keyEvent) override;
    // Отрисовка состояния игры на экране
    // window - окно, в котором будет происходить отрисовка
    void render(sf::RenderWindow& window) override;
};