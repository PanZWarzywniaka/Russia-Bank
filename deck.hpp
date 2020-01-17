#ifndef DECK_HPP
#define DECK_HPP

#include <SFML/Graphics.hpp>
#include <stack>
#include "card.hpp"

class Deck: public sf::Drawable
{
    private:

    std::stack<Card> pile;
    sf::FloatRect rect; //Rect<float>


    public:
    Deck() = delete;
    Deck(sf::FloatRect);
    
    bool empty() const;
    Card& top();
    const Card& top() const;
    size_t size() const;
    void push(const Card& val);
    void push(Card&& val);
    void pop();

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override; //ta funkcja ju nie jest wirtualna ale musimy ja nadpisac

};

#endif