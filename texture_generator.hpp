#ifndef TEXTURE_GEN_HPP
#define TEXTURE_GEN_HPP
#include <SFML/Graphics.hpp>
#include "card.hpp"

sf::Texture generate_card_texture(const Card&); 
sf::Image generate_textures();

#endif