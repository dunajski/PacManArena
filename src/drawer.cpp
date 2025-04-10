#include "game_entity.h"
#include "drawer.h"

#include <iostream>
#include <SFML/Graphics/Font.hpp>
#include "dot.h"
#include "power_dot.h"
#include "ghost.h"
#include "pacman.h"



Drawer::Drawer(sf::RenderWindow& window)
    : window(window), game_offset_x((1920 - 560) / 2.0f), game_offset_y((1080 - 620) / 2.0f) {}

void Drawer::draw_game_entities(const std::vector<std::unique_ptr<GameEntity>>& game_entities) {
    // first, draw Dot and PowerDot entities:
    for (auto& entity : game_entities) {
        if (!entity || !entity->is_e_visible() || !entity->get_shape())
            continue;

        if (dynamic_cast<Dot*>(entity.get()) || dynamic_cast<PowerDot*>(entity.get())) {
            sf::Shape* shape = entity->get_shape();

            auto draw_position = sf::Vector2f(
                game_offset_x + entity->get_position().x * tile_size + tile_size / 2.0f,
                game_offset_y + entity->get_position().y * tile_size + tile_size / 2.0f
            );

            shape->setPosition(draw_position);
            window.draw(*shape);
        }
    }

    // next, draw Ghost entities:
    for (auto& entity : game_entities) {
        if (!entity || !entity->is_e_visible() || !entity->get_shape())
            continue;

        if (dynamic_cast<Ghost*>(entity.get())) {
            sf::Shape* shape = entity->get_shape();

            auto draw_position = sf::Vector2f(
                game_offset_x + entity->get_position().x * tile_size + tile_size / 2.0f,
                game_offset_y + entity->get_position().y * tile_size + tile_size / 2.0f
            );

            shape->setPosition(draw_position);
            window.draw(*shape);
        }
    }

    // draw Pac-Man last
    for (auto& entity : game_entities) {
        if (!entity || !entity->is_e_visible() || !entity->get_shape())
            continue;

        // Check if the entity is Pac-Man.
        if (dynamic_cast<Pacman*>(entity.get())) {
            sf::Shape* shape = entity->get_shape();

            auto draw_position = sf::Vector2f(
                game_offset_x + entity->get_position().x * tile_size + tile_size / 2.0f,
                game_offset_y + entity->get_position().y * tile_size + tile_size / 2.0f
            );

            shape->setPosition(draw_position);
            window.draw(*shape);
        }
    }
}

void Drawer::draw_map(const std::vector<std::vector<int>>& grid)
{
    sf::RectangleShape wall(sf::Vector2f(tile_size, tile_size));
    wall.setOutlineColor(sf::Color::White);
    wall.setFillColor(sf::Color::Blue);
    wall.setOutlineThickness(1);

    for (size_t row = 0; row < grid.size(); ++row) {
        for (size_t col = 0; col < grid[row].size(); ++col)
        {
            int cell = grid[row][col];
            float x_pos = game_offset_x + col * tile_size;
            float y_pos = game_offset_y + row * tile_size;

            if (cell == 1)
            {
                wall.setPosition({x_pos, y_pos});
                window.draw(wall);
            }
        }
    }
}

void Drawer::draw_score(int score)
{
    static sf::Font font;
    static bool loaded = false;
    // std::filesystem::path path = std::filesystem::current_path();
    // std::cout << path.string() << std::endl;

    // https://www.dafont.com/minecraft.font
    // there will be problem with font path I think...
    if (!loaded) {
        if (!font.openFromFile("../bin/minecraft.ttf")) {
            std::cerr << "Failed to load font." << std::endl;
        }
        loaded = true;
    }

    sf::Text text(font);
    text.setFont(font);
    text.setString("Score: " + std::to_string(score));
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::Yellow);

    text.setPosition(sf::Vector2f{game_offset_x, game_offset_y - 40.f});

    window.draw(text);
}