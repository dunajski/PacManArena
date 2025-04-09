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

bool GameEntity::load_texture(const std::string& texture_path)
{
    const auto load_status = texture.loadFromFile(texture_path);
    if (load_status == false)
        std::cout << "Failed to load texture: " << texture_path << std::endl;
    return load_status;
}
