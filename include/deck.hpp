#ifndef DECK_HPP
#define DECK_HPP

#include <SFML/Graphics.hpp>
#include <stack>
#include <list>
#include "card.hpp"

class Deck: public sf::Drawable
{
    public:

    enum class Type
    {
        bank,
        outer_left,
        outer_right,
        players_main,
        trash
    };

    private:
    
    Type type;
    std::list<Card> pile;
    sf::FloatRect rect; //Rect<float> pozycja potem rozmiar
    sf::RectangleShape frame;

    public:

    Deck(Type);

    bool empty() const;
    Card& top();
    const Card& top() const;
    Card& begin();
    const Card& begin() const;
    size_t size() const;
    void push(const Card& val);
    void push(Card&& val);
    void pop();
    void pop_front();
    void reverse();
    void clear();
    sf::FloatRect get_rect() const; //służy do sprawdzenia czy kursor, kliknął na talię
    const Type get_type() const;

    void deck_scaling(sf::Vector2u);
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override; //ta funkcja ju nie jest wirtualna ale musimy ja nadpisac


};

#endif