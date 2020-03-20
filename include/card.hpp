#ifndef CARD_HPP
#define CARD_HPP

#include <SFML/Graphics.hpp>
#include <stack>
#include <array>


class Card: public sf::Drawable
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
    
    friend std::ostream &operator<<(std::ostream&,const Card&);

    public:
    //zaraz przerobie na consty
    static sf::Image card_sheet;
    static sf::Vector2f original_single_card_size;
    static sf::Vector2f actual_single_card_size;
    static std::array<sf::Texture, 52> texture_array; //ewntualnie rozszerze do 54 gdy będę miał tekstury rewersów kart
    


    //funkcje
    Card() = delete;
    Card(Value wart, Colour kol);
    Card(const Card&);
    Card(Card&&);
    
    bool operator<(const Card&) const;
    bool operator==(const Card&) const;
    

    Colour get_colour() const;
    Value get_value() const;
    bool is_black() const; //poprawne politycznie?
    static void load_texuture();
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override; //ta funkcja ju nie jest wirtualna ale musimy ja nadpisac
    void card_scaling();
    void setPosition(float,float);

};



#endif