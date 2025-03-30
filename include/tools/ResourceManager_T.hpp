#pragma once

#include <map>
#include <string>
#include <stdexcept>
#include "../utils/logging.h"

/**
 * Этот класс является шаблонным, поэтому его реализация находится в заголовочном файле.
 * Класс предназначен для загрузки ресурсов из файловой системы.
 * 
 * Обёрнут шаблонами Resource и Identifier. Первый может быть одним из трёх SFML классов:
 * sf::Texture, sf::Font, sf::SoundBuffer. Второй определяет enum class с идентификаторами
 * ресурсов: TextureKeys, FontKeys или SoundKeys.
 */

template <typename Resource, typename Identifier>
class ResourceManager {
private:
    // В этот словарь помещаются все загруженные ресурсы
    std::map<Identifier, Resource> resources;

public:
    // Метод для загрузки ресурсов. Принимает в качестве аргументов
    // название ресурса (name) и путь к нему (path)
    bool load(Identifier name, const std::string& path) {
        if (resources.find(name) != resources.end()) {
            errorLog("ResourceManager::load", "Ресурс уже загружен");
            return false;
        }
    
        Resource resource;
        if (!resource.loadFromFile(path)) {
            errorLog("ResourceManager::load", "Ошибка загрузки ресурса");
            return false;
        }
    
        // Помещаем ресурс в map
        resources[name] = std::move(resource);

        infoLog("ResourceManager::load", "Ресурс успешно загружен");
        return true;
    }

    // Метод, по которому можно получить соответствующий ресурс.
    // В качестве параметра передаётся название ресурса (name)
    Resource& get(Identifier name) {
        auto it = resources.find(name); // Ищет ресурс по имени внутри map
    
        // Если ресурс не найден
        if (it == resources.end()) {
            errorLog("ResourceManager::get", "Ресурс не найден");
            throw std::runtime_error("Resources not found");
        }
    
        // Если ресурс найден, it указывает на пару ключ-значение std::pair<Identifier, Resource>.
        // Возвращаем сам ресурс, т.е. второе значение

        infoLog("ResourceManager::get", "Ресурс успешно получен");
        return it->second;
    }

    // Вырезает из текстуры с именем (sourceTextureName) прямоугольник с координатами (rect).
    // Помещает текстуру в resources с именем (name) и возвращает текстуру sf::Texture
    // Полезно, когда из тайлсета нужно вырезать один конкретный тайл
    template <typename T = Resource>
    std::enable_if_t<std::is_same_v<T, sf::Texture>, sf::Texture&>
    getSubTexture(Identifier sourceTextureName, Identifier name, const sf::IntRect& rect) {
        auto it = resources.find(name);
        if (it != resources.end()) return it->second;

        const auto& sourceTexture = get(sourceTextureName);

        sf::Texture subTexture;
        if (!subTexture.loadFromImage(sourceTexture.copyToImage(), false, rect)) {
            errorLog("ResourceManager::getSubTexture", "Ошибка загрузки подтекстуры");
            throw std::runtime_error("Failed to load subtexture");
        }
        resources[name] = std::move(subTexture);

        infoLog("ResourceManager::getSubTexture", "Подтекстура получена");
        return resources[name];
    }
};