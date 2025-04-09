#include "game.h"
#include "pacman.h"

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
    auto pacman = std::make_unique<Pacman>();
    pacman->init_shape(460.0f/25.0f);
    pacman->make_visible();
    add_game_entity(std::move(pacman), {5,5});

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
