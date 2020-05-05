#include "texture_generator.hpp"
/*
sf::Image generate_textures()
{
    sf::RenderTexture ret;
    ret.create(640,4160);
    for(std::size_t i = 0; i<4 ; i++)
    {
        for(std::size_t j = 0; j<13 ; j++)
        {
            sf::Sprite renderowana_karta(generate_card_texture(Card(static_cast<Card::Value>(j),static_cast<Card::Suit>(i))));
            renderowana_karta.setPosition(sf::Vector2f(160*i,320*j));
            ret.draw(renderowana_karta);
        }
    }
    return ret.getTexture().copyToImage();
}


sf::Texture generate_card_texture(const Card& karta)
{
    sf::RenderTexture ret;
    ret.create(160,320);
    Card::Colour kolor;
    Card::Value wartosc;
    kolor = karta.get_colour();
    wartosc = karta.get_value();

    ret.clear(sf::Color::White);




    return sf::Texture(ret.getTexture());
}

*/