#pragma once
#include <iostream>

#include "game_entity.h"

class Pacman : public GameEntity {
public:
    Pacman() {std::cout << "Pacman constructor" << std::endl;}
    ~Pacman() = default;
};
