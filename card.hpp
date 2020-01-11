#ifndef CARD_HPP
#define CARD_HPP

#include <SFML/Graphics.hpp>
#include<stack>


class Card
{
    public: //do zmiany
    
    enum class Value
    {
        Ace,
        _2,
        _3,
        _4,
        _5,
        _6,
        _7,
        _8,
        _9,
        _10,
        J,
        Q,
        K
    };

    enum class Colour
    {
        hearths,
        dimonds,
        spades,
        clubs
    };

    private:

    Value wartosc;
    Colour kolor;
    sf::Sprite card_sprite;
    

    public:

    static sf::Texture card_sheet;
    static sf::Vector2f single_card_size;

    //funkcje
    Card() = delete;
    Card(Value wart, Colour kol);
    Card(const Card&);
    Card(Card&&);
    bool operator<(const Card&) const;
    Colour get_colour() const;
    Value get_value() const;
    bool is_black() const; //poprawne politycznie?
    static void load_texuture();
    //static sf::Vector2f single_card_size(sf::View);

};



#endif