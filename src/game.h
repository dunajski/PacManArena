#pragma once
#include "common.h"
#include <vector>
#include <memory>

class GameEntity;

struct Position {
    int x;
    int y;

    Position(int x = 0, int y = 0) : x(x), y(y) {}
};

class Game
{
private:
    int lives_remaining{3};
    int score{0};
    EGameState game_state{EGameState::NOT_STARTED};
    std::vector<std::unique_ptr<GameEntity>> game_entities;
public:
    Game() = default;
    ~Game() = default;

    bool start_game();
    bool end_game();
    bool load_game_entities();
    bool add_game_entity(std::unique_ptr<GameEntity> entity, const Position& position);
    const std::vector<std::unique_ptr<GameEntity>>& get_all_entities() const;
};

