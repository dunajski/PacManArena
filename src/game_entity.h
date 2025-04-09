#pragma once
#include "SFML/Graphics/Texture.hpp"
#include "game.h" // Include for Position struct

class GameEntity {
private:
    sf::Texture texture;
    sf::Vector2f position = sf::Vector2f(0, 0);
    bool is_visible{false}; // at first shall be set position and then make it visible
public:
    GameEntity();
    ~GameEntity();

    sf::Vector2f get_position() const {return position;}
    void set_position(float x, float y);
    void set_position(const Position& pos); // Overloaded function

    void make_visible() {is_visible = true;}
    void make_invisible() {is_visible = false;}

    bool load_texture(const std::string& texture_path);
    const sf::Texture& get_texture() const {return texture;}
};
