#include "game.h"
#include "pacman.h"
#include "ghost.h"
#include "dot.h"
#include "power_dot.h"

bool Game::start_game()
{
    // try to load all entites
    if (!load_game_entities())
    {
        return false;
    }
    return true;
}

bool Game::load_game_entities()
{
    // it should be taken from drawer
    // https://github.com/dunajski/PacManArena/issues/6
    constexpr float tile = 560.0f / 25.0f;

    auto pacman = std::make_unique<Pacman>();
    pacman->init_shape(tile);
    pacman->make_visible();
    add_game_entity(std::move(pacman), {5, 5});

    auto ghost = std::make_unique<Ghost>();
    ghost->init_shape(tile);
    ghost->make_visible();
    add_game_entity(std::move(ghost), {7, 5});

    auto dot = std::make_unique<Dot>();
    dot->init_shape(tile);
    dot->make_visible();
    add_game_entity(std::move(dot), {10, 10});

    auto power_dot = std::make_unique<PowerDot>();
    power_dot->init_shape(tile);
    power_dot->make_visible();
    add_game_entity(std::move(power_dot), {13, 13});

    return true;
}

bool Game::add_game_entity(std::unique_ptr<GameEntity> entity, const Position& position)
{
    if (position.x < 0 || position.y < 0) // Validate position
    {
        std::cerr << "Invalid position: (" << position.x << ", " << position.y << ")" << std::endl;
        return false;
    }

    entity->set_position(position); // Set the position of the entity
    game_entities.push_back(std::move(entity));

    return true;
}

const std::vector<std::unique_ptr<GameEntity>>& Game::get_all_entities() const
{
    return game_entities;
}

void Game::initialize_map()
{
    map_layout = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 1},
        {1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 2, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1},
        {1, 2, 1, 0, 1, 2, 1, 0, 1, 2, 2, 1, 0, 2, 1, 0, 1, 2, 1, 2, 1},
        {1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 2, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1},
        {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
        {1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1},
        {1, 2, 1, 0, 1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1, 0, 1, 2, 1, 2, 1},
        {1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1},
        {1, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1},
        {1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1},
        {1, 2, 1, 0, 0, 0, 1, 2, 1, 0, 1, 0, 1, 2, 1, 0, 0, 0, 1, 2, 1},
        {1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1},
        {1, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1},
        {1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 2, 1},
        {1, 2, 1, 0, 1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1, 2, 1, 2, 1},
        {1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1},
        {1, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };
}
