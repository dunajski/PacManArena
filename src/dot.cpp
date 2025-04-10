#include "dot.h"
#include "SFML/Graphics.hpp"
#include <iostream>

Dot::Dot() {
    std::cout << "Dot created" << std::endl;
}

void Dot::init_shape(float tile_size) {
    auto circle = std::make_unique<sf::CircleShape>(tile_size / 6);
    circle->setFillColor(sf::Color::White);
    circle->setOrigin(sf::Vector2f(circle->getRadius(), circle->getRadius()));
    set_shape(std::move(circle));
}
