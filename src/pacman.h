#pragma once
#include <iostream>
#include "game_entity.h"

class Pacman : public GameEntity {
public:
    Pacman() {std::cout << "Pacman constructor" << std::endl;}
    ~Pacman() override = default;
    void init_shape(float tile_size) override;

    void update(float dt, const std::vector<std::vector<int>>& map_data) override;

    void set_direction(MoveDirection direction);

private:
    MoveDirection curr_direction = MoveDirection::RIGHT; // actual direction
    MoveDirection requested_direction = MoveDirection::NO_DIR;
    float speed = 4.0f;  // how many tiles per second

    float time_acc = 0.0f;

    // checks that can move to position 'pos' according to layout - 'map_data'
    bool can_move_to(Position pos, const std::vector<std::vector<int>>& map_data);
};
