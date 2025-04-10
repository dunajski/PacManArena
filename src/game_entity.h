#pragma once
#include "SFML/Graphics/Texture.hpp"
#include "common.h"
#include "SFML/Graphics/Shape.hpp"

class GameEntity {
private:
    sf::Vector2i position = sf::Vector2i(0, 0);
    bool is_visible{false}; // at first shall be set position and then make it visible
    std::unique_ptr<sf::Shape> shape;
public:
    GameEntity();
    virtual ~GameEntity();

    sf::Vector2i get_position() const {return position;}
    void set_position(int x, int y);
    void set_position(const Position& pos);

    void make_visible() {is_visible = true;}
    void make_invisible() {is_visible = false;}
    bool is_e_visible() const {return is_visible;}

    virtual void init_shape(float tile_size);
    sf::Shape* get_shape() const { return shape.get(); }

    // all game entities (if needed) shall have their own update method that 'move' them between
    // dt - delta_time according to map_data
    // I want to use delta_time to draw every dt instead of every frame
    virtual void update(float dt, const std::vector<std::vector<int>>& map_data) {}
protected:
    void set_shape(std::unique_ptr<sf::Shape> new_shape);
};
