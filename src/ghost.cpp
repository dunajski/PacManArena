#include "ghost.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <random>

Ghost::Ghost() {
    std::cout << "Ghost created" << std::endl;
}

void Ghost::init_shape(float tile_size) {
    const float ghost_width = tile_size - 8.f;
    const float ghost_height = tile_size - 8.f;

    auto rect = std::make_unique<sf::RectangleShape>(sf::Vector2f(ghost_width, ghost_height));
    rect->setFillColor(sf::Color::Red);
    rect->setOutlineColor(sf::Color::White);
    rect->setOutlineThickness(1.0f);
    rect->setOrigin(sf::Vector2f(ghost_width/2.f, ghost_height/2.f));
    set_shape(std::move(rect));
}

bool Ghost::can_move_to(int x, int y, const std::vector<std::vector<int>>& map_data)
{
    if (y < 0 || y >= (int)map_data.size()) return false;
    if (x < 0 || x >= (int)map_data[y].size()) return false;

    if (map_data[y][x] == 1) return false;
    return true;
}

void Ghost::pick_new_rnd_dir(const std::vector<std::vector<int>>& map_data)
{
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_int_distribution<int> dist(0, 3);

    MoveDirection dir = static_cast<MoveDirection>(dist(rng));
    curr_direction = dir;
}

void Ghost::update(float dt, const std::vector<std::vector<int>>& map_data)
{
    static std::mt19937 rng(std::random_device{}());
    time_acc += dt;
    float step_time = 1.0f / speed;

    while (time_acc >= step_time)
    {
        time_acc -= step_time;

        auto pos = get_position();
        int new_x = pos.x;
        int new_y = pos.y;

        switch (curr_direction) {
            case MoveDirection::UP:    new_y -= 1; break;
            case MoveDirection::DOWN:  new_y += 1; break;
            case MoveDirection::LEFT:  new_x -= 1; break;
            case MoveDirection::RIGHT: new_x += 1; break;
            default: break;
        }

        if (!can_move_to(new_x, new_y, map_data))
        {
            pick_new_rnd_dir(map_data);
        }
        else
        {
            set_position(new_x, new_y);

            if (std::uniform_int_distribution(0, 9)(rng) == 0) {
                pick_new_rnd_dir(map_data);
            }
        }
    }
}