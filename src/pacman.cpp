#include "pacman.h"
#include <cmath>
#include "SFML/Graphics.hpp"
#include <SFML/Graphics/ConvexShape.hpp>

void Pacman::init_shape(float tile_size) {
    // auto circle = std::make_unique<sf::CircleShape>(tile_size/2);
    // circle->setFillColor(sf::Color::Yellow);
    // set_shape(std::move(circle));

    // ...this was made with ChatGPT
    const unsigned int point_count = 50;

    // Create a convex shape – essentially a circle with a missing slice
    auto pacman_shape = std::make_unique<sf::ConvexShape>();
    // +2 because we add a center point and one to close the arc
    pacman_shape->setPointCount(point_count + 2);

    float radius = tile_size / 2.5f;
    // Value in radians; ~80° mouth opening = 40° on each side
    float start_angle = 40.0f * 3.14159265f / 180.0f;
    float end_angle   = 2.0f * 3.14159265f - start_angle;
    float angle_step  = (end_angle - start_angle) / static_cast<float>(point_count);

    // Set the origin to the center – so (0,0) will be the shape's center
    // which makes rotation/positioning easier
    pacman_shape->setOrigin(sf::Vector2f(radius, radius));

    // The first point is the center (0,0) in local coordinates
    pacman_shape->setPoint(0, sf::Vector2f(0.f, 0.f));

    // Points from 1 to pointCount+1 define the arc
    for (unsigned int i = 0; i <= point_count; ++i)
    {
        float angle = start_angle + i * angle_step;
        float x = radius * std::cos(angle);
        float y = radius * std::sin(angle);
        pacman_shape->setPoint(i + 1, sf::Vector2f(x, y));
    }

    pacman_shape->setFillColor(sf::Color::Yellow);

    // https://www.sfml-dev.org/documentation/3.0.0/namespacesf.html#a701020eb396e62ba560619e68c689a38
    auto bounds = pacman_shape->getLocalBounds();

    float center_x = bounds.position.x + bounds.size.x / 2.f;
    float center_y = bounds.position.y + bounds.size.y / 2.f;

    pacman_shape->setOrigin(sf::Vector2f{center_x, center_y});

    // Finally, pass our completed shape to set_shape
    set_shape(std::move(pacman_shape));
}
