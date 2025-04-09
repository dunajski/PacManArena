#include "power_dot.h"
#include <iostream>
#include "SFML/Graphics.hpp"

PowerDot::PowerDot() {
    std::cout << "PowerDot created" << std::endl;
}

void PowerDot::init_shape(float tile_size) {
    auto circle = std::make_unique<sf::CircleShape>(tile_size / 3);
    circle->setFillColor(sf::Color::Blue);
    set_shape(std::move(circle));
}