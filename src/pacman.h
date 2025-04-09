#pragma once
#include <iostream>

#include "game_entity.h"

class Pacman : public GameEntity {
public:
    Pacman() {std::cout << "Pacman constructor" << std::endl;}
    ~Pacman() override = default;
    void init_shape(float tile_size) override;
};
