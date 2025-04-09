#include "ghost.h"
#include "SFML/Graphics.hpp"
#include <iostream>

Ghost::Ghost() {
    std::cout << "Ghost created" << std::endl;
}

void Ghost::init_shape(float tile_size) {
    auto rect = std::make_unique<sf::RectangleShape>(sf::Vector2f(tile_size, tile_size));
    rect->setFillColor(sf::Color::Red);
    set_shape(std::move(rect));
}
