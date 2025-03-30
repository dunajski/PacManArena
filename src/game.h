#pragma once
#include "common.h"
#include "game_entity.h"
#include <vector>

class Game
{
private:
    int lives_remaining{3};
    int score{0};
    EGameState game_state{EGameState::NOT_STARTED};
    std::vector<std::unique_ptr<GameEntity>>game_entities;
public:
    Game() = default;
    ~Game() = default;

    bool start_game();
    bool end_game();
    bool load_game_entities();
    bool add_game_entity(std::unique_ptr<GameEntity> entity);
};

