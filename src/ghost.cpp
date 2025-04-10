#include "ghost.h"
#include "SFML/Graphics.hpp"
#include <iostream>

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
