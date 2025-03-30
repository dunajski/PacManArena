#pragma once
#include "SFML/Graphics/Texture.hpp"

class GameEntity {
private:
    sf::Texture texture;
    sf::Vector2i position = sf::Vector2i(0, 0);
    bool is_visible{false}; // at first shall be set position and then make it visible
public:
    GameEntity();
    ~GameEntity();

    sf::Vector2i get_position() const {return position;}
    void set_position(int x, int y);

    void make_visible() {is_visible = true;}
    void make_invisible() {is_visible = false;}

    bool load_texture(const std::string& texture_path);
    const sf::Texture& get_texture() const {return texture;}
};
