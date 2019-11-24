#ifndef CARD_HPP
#define CARD_HPP

#include<stack>


class Card
{
    public: //do zmiany
    
    enum class Value
    {
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
        K,
        Ace
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

    public:
    
    Card();
    Card(Value wart, Colour kol);

    Colour get_colour() const;
    Value get_value() const;

    friend class Game;
};

#endif