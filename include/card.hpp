#ifndef CARD_HPP
#define CARD_HPP

#include <SFML/Graphics.hpp>
#include <stack>
#include <array>


class Card: public sf::Drawable
{
    public: 
    
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

    enum class Suit
    {
        hearths,
        dimonds,
        spades,
        clubs
    };

    private:

    Value value;
    Suit suit;
    sf::Sprite card_sprite;
    static sf::Vector2f default_single_card_size; //przechowuje domyślny rozmiar karty
    static float card_scale; 
    static std::array<sf::Texture, 52> texture_array; //ewntualnie rozszerze do 54 gdy będę miał tekstury rewersów kart
    
    friend std::ostream &operator<<(std::ostream&,const Card&);

    public:

    Card() = delete;
    Card(Value wart, Suit kol);
    Card(const Card&);
    Card(Card&&);
    
    bool operator<(const Card&) const;
    bool operator==(const Card&) const;
    
    Suit get_suit() const;
    Value get_value() const;
    bool is_black() const; //poprawne politycznie?
    void setPosition(float,float);
    void setRotation(float angle);

    static void load_texuture();
    static sf::Vector2f get_default_single_card_size();
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override; //ta funkcja ju nie jest wirtualna ale musimy ja nadpisac
    void card_scaling(sf::Vector2u position);
};

#endif