#include "../../include/tools/StaticObjectFactory.hpp"

#include "../../include/entities/static_objects/Letter.hpp"
#include "../../include/utils/logging.h"

StaticObjectFactory::StaticObjectFactory() {
    // Регистрация статических объектов
    registerObject("Letter", [](sf::Vector2f position, sf::Sprite sprite, const json& objectData) {
        return std::make_unique<Letter>(position, sprite, objectData["letter_text"].get<std::string>());
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
    const json& objectData, sf::Vector2f position, sf::Sprite sprite
){
    auto it = creators.find(objectData["object_name"]);
    if (it != creators.end()) {
        // Вызов метода создания объекта по имени
        // it->second - это функция, которая создаёт объект (Creator)
        return it->second(position, sprite, objectData);
    } else {
        errorLog("StaticObjectFactory::createObject", 
            "Объект " + objectData["object_name"].get<std::string>() + " не зарегистрирован"
        );
        return nullptr;
    }
}