#pragma once
#include "game_entity.h"

class Dot : public GameEntity {
public:
    Dot();
    void init_shape(float tile_size) override;
};