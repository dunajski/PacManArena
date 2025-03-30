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
    add_game_entity(std::make_unique<Pacman>());

    // DEBUG, shall be removed later
    // print all game entities positions
    for (const auto& ge : game_entities)
    {
        auto position = ge->get_position();
        std::cout << position.x << " " << position.y << std::endl;
    }

    return true;
}

bool Game::add_game_entity(std::unique_ptr<GameEntity> entity)
{
    game_entities.push_back(std::move(entity));

    return true;
}
