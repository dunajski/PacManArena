#pragma once
#include "game_entity.h"

class Ghost : public GameEntity {
public:
    Ghost();
    void init_shape(float tile_size) override;
};
