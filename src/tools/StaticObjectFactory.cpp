#include "../../include/tools/StaticObjectFactory.hpp"

#include "../../include/entities/static_objects/Letter.hpp"
#include "../../include/utils/logging.h"

StaticObjectFactory::StaticObjectFactory() {
    // Регистрация статических объектов
    registerObject("Letter", [](sf::Vector2f position, sf::Sprite sprite) {
        return std::make_unique<Letter>(position, sprite);
    });
}

StaticObjectFactory& StaticObjectFactory::getInstance() {
    static StaticObjectFactory instance; // Создаём единственный экземпляр класса
    return instance;
}

void StaticObjectFactory::registerObject(const std::string &objectName, Creator creator) {
    creators[objectName] = creator;
}

std::unique_ptr<StaticObject> StaticObjectFactory::createObject(
    const std::string &objectName, sf::Vector2f position, sf::Sprite sprite
){
    auto it = creators.find(objectName);
    if (it != creators.end()) {
        // Вызов метода создания объекта по имени
        // it->second - это функция, которая создаёт объект (Creator)
        return it->second(position, sprite);
    } else {
        errorLog("StaticObjectFactory::createObject", "Объект " + objectName + " не зарегистрирован");
        return nullptr;
    }
}