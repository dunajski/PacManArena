#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "game_entity.h"

class Drawer {
public:
    Drawer(sf::RenderWindow& window, float view_width = 1920.f, float view_height = 1080.f);
    float get_tile_size() const {return tile_size;}
    void draw_map(const std::vector<std::vector<int>>& grid);
    void draw_game_entities(const std::vector<std::unique_ptr<GameEntity>>& game_entities);
    void draw_score(int score);
private:
    sf::RenderWindow& window;
    static constexpr float tile_size = 560.0f / 25.0f;
    float game_offset_x;
    float game_offset_y;
};
