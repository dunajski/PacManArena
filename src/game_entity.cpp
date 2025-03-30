#include "game_entity.h"

#include <iostream>

void GameEntity::set_position(int x, int y)
{
    position = sf::Vector2i(x, y);
}

GameEntity::GameEntity()
{
    std::cout << "Game Entity created" << std::endl;
}

GameEntity::~GameEntity()
{
    std::cout << "Game Entity destroyed" << std::endl;
    position = sf::Vector2i(0, 0);
    is_visible = false;
}

bool GameEntity::load_texture(const std::string& texture_path)
{
    const auto load_status = texture.loadFromFile(texture_path);
    if (load_status == false)
        std::cout << "Failed to load texture: " << texture_path << std::endl;
    return load_status;
}
