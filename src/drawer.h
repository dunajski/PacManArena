#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "game_entity.h"

class Drawer {
public:
    Drawer(sf::RenderWindow& window);
    void draw_grid(const std::vector<std::vector<int>>& grid);
    void draw_entities(const std::vector<sf::Vector2f>& entity_positions);
    void draw_game_entities(const std::vector<std::unique_ptr<GameEntity>>& game_entities);
private:
    sf::RenderWindow& window;
    float tileSize;
    float gameOffsetX;
    float gameOffsetY;
};
