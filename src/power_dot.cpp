#include "power_dot.h"
#include <iostream>
#include "SFML/Graphics.hpp"

PowerDot::PowerDot() {
    std::cout << "PowerDot created" << std::endl;
}

void PowerDot::init_shape(float tile_size) {
    auto circle = std::make_unique<sf::CircleShape>(tile_size / 3);
    circle->setFillColor(sf::Color::Magenta);
    circle->setOutlineColor(sf::Color::White);
    circle->setOrigin(sf::Vector2f(circle->getRadius(), circle->getRadius()));
    circle->setOutlineThickness(1.0f);
    set_shape(std::move(circle));
}