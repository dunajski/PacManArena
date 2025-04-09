#pragma once
#include "SFML/Graphics/Texture.hpp"
#include "game.h" // Include for Position struct
#include "SFML/Graphics/Shape.hpp"

class GameEntity {
private:
    sf::Vector2f position = sf::Vector2f(0, 0);
    bool is_visible{false}; // at first shall be set position and then make it visible
    std::unique_ptr<sf::Shape> shape;
public:
    GameEntity();
    virtual ~GameEntity();

    sf::Vector2f get_position() const {return position;}
    void set_position(float x, float y);
    void set_position(const Position& pos);

    void make_visible() {is_visible = true;}
    void make_invisible() {is_visible = false;}
    bool is_e_visible() const {return is_visible;}

    virtual void init_shape(float tile_size);
    sf::Shape* get_shape() const { return shape.get(); }
protected:
    void set_shape(std::unique_ptr<sf::Shape> new_shape);
};
