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
    // adds Pac-Man, Ghosts, dots and power dots, according to `map_layout`
    set_entities_positions();

    return true;
}

bool Game::add_game_entity(std::unique_ptr<GameEntity> entity, const Position& position)
{
    // position should be bound not onlt to 0 but to max posistion too
    if (position.x < 0 || position.y < 0)
    {
        std::cerr << "Invalid position: (" << position.x << ", " << position.y << ")" << std::endl;
        return false;
    }

    entity->set_position(position);
    game_entities.push_back(std::move(entity));

    return true;
}

const std::vector<std::unique_ptr<GameEntity>>& Game::get_all_entities() const
{
    return game_entities;
}

void Game::initialize_map()
{
    // 1 - wall
    // 2 - dot
    // 3 - power_dot
    // 0 - nothing, routes to move by Pac-Man and Ghosts
    // 4 - Pac-Man starting position
    // 5 - Ghosts starting positions
    map_layout = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 1},
        {1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 2, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1},
        {1, 2, 1, 0, 1, 2, 1, 0, 1, 2, 2, 1, 0, 2, 1, 0, 1, 2, 1, 2, 1},
        {1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 2, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1},
        {1, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
        {1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1},
        {1, 2, 1, 0, 1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1, 0, 1, 2, 1, 2, 1},
        {1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1},
        {1, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1},
        {1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1},
        {1, 2, 1, 0, 0, 0, 1, 2, 1, 0, 1, 0, 1, 2, 1, 0, 0, 0, 1, 2, 1},
        {1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1},
        {1, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 1, 2, 5, 2, 5, 2, 5, 2, 1},
        {1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 2, 1},
        {1, 2, 1, 0, 1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1, 2, 1, 2, 1},
        {1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1},
        {1, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };
}

void Game::set_entities_positions()
{
    // it should be taken from drawer
    // https://github.com/dunajski/PacManArena/issues/6
    constexpr float tile = 560.0f / 25.0f;

    for (size_t row = 0; row < map_layout.size(); ++row)
    {
        for (size_t col = 0; col < map_layout[row].size(); ++col)
        {
            int cell = map_layout[row][col];
            int x_pos = col;
            int y_pos = row;

            if (cell == 2)
            {
                auto dot = std::make_unique<Dot>();
                dot->init_shape(tile);
                dot->make_visible();
                add_game_entity(std::move(dot), {x_pos, y_pos});
            }
            else if (cell == 3)
            {
                auto p_dot = std::make_unique<PowerDot>();
                p_dot->init_shape(tile);
                p_dot->make_visible();
                add_game_entity(std::move(p_dot), {x_pos, y_pos});
            }
            else if (cell == 4)
            {
                auto pacman = std::make_unique<Pacman>();
                pacman->init_shape(tile);
                pacman->make_visible();
                auto raw_ptr = pacman.get();
                add_game_entity(std::move(pacman), {x_pos, y_pos});
                pacman_ptr = raw_ptr;
            }
            else if (cell == 5)
            {
                auto ghost = std::make_unique<Ghost>();
                ghost->init_shape(tile);
                ghost->make_visible();
                add_game_entity(std::move(ghost), {x_pos, y_pos});
            }
        }
    }
}

void Game::update(float dt)
{
    for (auto& entity : game_entities)
    {
        if (entity && entity->is_e_visible())
        {
            entity->update(dt, map_layout);
        }
    }

    sf::Vector2i pac_man_pos = pacman_ptr->get_position();

    // iterate over entities
    for (int i = game_entities.size() - 1; i >= 0; --i)
    {
        auto& e = game_entities[i];
        if (!e) continue;

        // if entity position equeals pac-man pos...
        if (e->get_position() == pac_man_pos)
        {
            // ... if it is 'Dot'
            if (dynamic_cast<Dot*>(e.get()))
            {
                score += 10;
                game_entities.erase(game_entities.begin() + i);
            }
            else if (dynamic_cast<PowerDot*>(e.get())) // ... or 'PowerDot'
            {
                score += 50;
                game_entities.erase(game_entities.begin() + i);
            }
        }
    }
}