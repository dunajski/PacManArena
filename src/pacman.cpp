#include "pacman.h"
#include <cmath>
#include "SFML/Graphics.hpp"
#include <SFML/Graphics/ConvexShape.hpp>

void Pacman::init_shape(float tile_size) {
    // auto circle = std::make_unique<sf::CircleShape>(tile_size/2);
    // circle->setFillColor(sf::Color::Yellow);
    // set_shape(std::move(circle));

    // ...this was made with ChatGPT
    const unsigned int pointCount = 100;

    // Create a convex shape – essentially a circle with a missing slice
    auto pacmanShape = std::make_unique<sf::ConvexShape>();
    // +2 because we add a center point and one to close the arc
    pacmanShape->setPointCount(pointCount + 2);

    float radius = tile_size / 2.0f;
    // Value in radians; ~80° mouth opening = 40° on each side
    float startAngle = 40.0f * 3.14159265f / 180.0f;
    float endAngle   = 2.0f * 3.14159265f - startAngle;
    float angleStep  = (endAngle - startAngle) / static_cast<float>(pointCount);

    // Set the origin to the center – so (0,0) will be the shape's center
    // which makes rotation/positioning easier
    pacmanShape->setOrigin(sf::Vector2f(radius, radius));

    // The first point is the center (0,0) in local coordinates
    pacmanShape->setPoint(0, sf::Vector2f(0.f, 0.f));

    // Points from 1 to pointCount+1 define the arc
    for (unsigned int i = 0; i <= pointCount; ++i)
    {
        float angle = startAngle + i * angleStep;
        float x = radius * std::cos(angle);
        float y = radius * std::sin(angle);
        pacmanShape->setPoint(i + 1, sf::Vector2f(x, y));
    }

    pacmanShape->setFillColor(sf::Color::Yellow);

    // Finally, pass our completed shape to set_shape
    set_shape(std::move(pacmanShape));
}
