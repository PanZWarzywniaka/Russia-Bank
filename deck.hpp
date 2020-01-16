#ifndef DECK_HPP
#define DECK_HPP

#include <SFML/Graphics.hpp>
#include <stack>
#include "card.hpp"

class Deck
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

};

#endif