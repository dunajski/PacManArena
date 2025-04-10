#pragma once
#include "common.h"
#include <vector>
#include <memory>
#include "pacman.h"

class GameEntity;
class Pacman;
class Game
{
private:
    int lives_remaining{3};
    int score{0};
    EGameState game_state{EGameState::NOT_STARTED};
    std::vector<std::unique_ptr<GameEntity>> game_entities;
    std::vector<std::vector<int>> map_layout;
    Pacman* pacman_ptr {nullptr};
public:
    Game() = default;
    ~Game() = default;

    bool start_game();
    bool end_game();
    bool load_game_entities();
    bool add_game_entity(std::unique_ptr<GameEntity> entity, const Position& position);
    const std::vector<std::unique_ptr<GameEntity>>& get_all_entities() const;

    void initialize_map();

    const std::vector<std::vector<int>>& get_map_layout() const { return map_layout; }
    void set_entities_positions();

    Pacman* get_pacman() const { return pacman_ptr;}

    void update(float dt);
};

