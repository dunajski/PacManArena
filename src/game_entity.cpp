#include "game_entity.h"

#include <iostream>

void GameEntity::set_position(float x, float y)
{
    if (x < 0 || y < 0) // Validate position
    {
        std::cerr << "Invalid position: (" << x << ", " << y << ")" << std::endl;
        return;
    }
    position = sf::Vector2f(x, y);
}

void GameEntity::set_position(const Position& pos)
{
    set_position(pos.x, pos.y); // Delegate to the existing function
}

GameEntity::GameEntity()
{
    std::cout << "Game Entity created" << std::endl;
}

GameEntity::~GameEntity()
{
    std::cout << "Game Entity destroyed" << std::endl;
    is_visible = false; // Keep this if visibility needs to be reset
}

void GameEntity::set_shape(std::unique_ptr<sf::Shape> new_shape) {
    shape = std::move(new_shape);
    if (shape)
        shape->setPosition(position);
}
void GameEntity::init_shape(float tile_size) {
    // by default nothing, shall be done in derivied class
}
