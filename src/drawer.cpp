#include "game_entity.h"
#include "drawer.h"
#include "SFML/Graphics/Sprite.hpp"
#include "game.h"

Drawer::Drawer(sf::RenderWindow& window)
    : window(window), tileSize(560.0f / 25.0f), gameOffsetX((1920 - 560) / 2.0f), gameOffsetY((1080 - 620) / 2.0f) {}

void Drawer::draw_grid(const std::vector<std::vector<int>>& grid) {
    sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
    tile.setOutlineColor(sf::Color::Blue);
    tile.setOutlineThickness(3);
    tile.setFillColor(sf::Color::Green);

    for (size_t y = 0; y < grid.size(); ++y) {
        for (size_t x = 0; x < grid[y].size(); ++x) {
            if (grid[y][x] == 1) { // Example: 1 represents a wall
                tile.setPosition({gameOffsetX + x * tileSize, gameOffsetY + y * tileSize});
                window.draw(tile);
            }
        }
    }
}

void Drawer::draw_entities(const std::vector<sf::Vector2f>& entity_positions) {
    sf::CircleShape entity{tileSize / 4};
    entity.setFillColor(sf::Color::Yellow);
    auto r = std::rand();
    r = r % 10;
    for (const auto& position : entity_positions) {
        entity.setPosition({gameOffsetX + position.x * tileSize+ tileSize/4, gameOffsetY + position.y * tileSize+tileSize/4 });
        window.draw(entity);
    }
}

void Drawer::draw_game_entities(const std::vector<std::unique_ptr<GameEntity>>& game_entities) {
    for (const auto& entity : game_entities) {
        // if (entity->get_texture().getSize() != sf::Vector2u(0, 0)) {
            // sf::Sprite sprite(entity->get_texture());
            // sprite.setPosition(sf::Vector2f(entity->get_position().x, entity->get_position().y));
            // window.draw(sprite);
            sf::RectangleShape test(sf::Vector2f(tileSize, tileSize));
            test.setOutlineColor(sf::Color::Blue);
            test.setOutlineThickness(3);
            test.setFillColor(sf::Color::Red);
            test.setPosition(sf::Vector2f(gameOffsetX + entity->get_position().x, gameOffsetY + entity->get_position().y));
            entity->set_position(entity->get_position().x > gameOffsetX ? gameOffsetX : entity->get_position().x+0.4, entity->get_position().y > gameOffsetY ? gameOffsetY : entity->get_position().y+0.7);
            window.draw(test);
        // }
    }
}
