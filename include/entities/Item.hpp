#pragma once

#include "Entity.hpp"

class Item : public Entity {
public:
    Item(/* args */);

    void use();
    void pickup();
};
