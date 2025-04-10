#pragma once
#include "SFML/Graphics/Texture.hpp"
#include "common.h"
#include "SFML/Graphics/Shape.hpp"

/**
 * @brief Base class for all game entities (Pacman, Ghost, Dot, PowerDot).
 */
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

    /**
     * @brief Updates the entity's logic each frame.
     * @param dt Delta time since last update.
     * @param map_data Layout data of the game map.
     */
    virtual void update(float dt, const std::vector<std::vector<int>>& map_data) {}
protected:
    void set_shape(std::unique_ptr<sf::Shape> new_shape);
};
