#pragma once
#include "game_entity.h"

/**
 * @brief Class representing a Ghost enemy.
 */
class Ghost : public GameEntity {
public:
    Ghost();
    void init_shape(float tile_size) override;

    void update(float dt, const std::vector<std::vector<int>>& map_data) override;

private:
    MoveDirection curr_direction;
    float speed = 2.0f;
    float time_acc = 0.0f;

    bool can_move_to(int x, int y, const std::vector<std::vector<int>>& map_data);
    void pick_new_rnd_dir(const std::vector<std::vector<int>>& map_data);
};
