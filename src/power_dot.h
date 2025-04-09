#pragma once
#include "game_entity.h"

class PowerDot : public GameEntity {
public:
    PowerDot();
    void init_shape(float tile_size) override;
};