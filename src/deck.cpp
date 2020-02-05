#include "deck.hpp"

Deck::Deck(sf::FloatRect prostokat)
:pile(std::stack<Card>())
{
    rect=prostokat;
    frame.setPosition(prostokat.left,prostokat.top);
    frame.setSize({prostokat.width,prostokat.height});
    frame.setFillColor(sf::Color::Transparent);
    frame.setOutlineColor(sf::Color::Black);
    frame.setOutlineThickness(2);
}

bool Deck::empty() const
{
    return pile.empty();    
}

Card& Deck::top()
{
    return pile.top();
}

const Card& Deck::top() const
{
    return pile.top();
}

size_t Deck::size() const
{
    return pile.size();
}

void Deck::push(const Card& val)
{
    pile.push(val);
    this->top().setPosition(this->rect.left,this->rect.top);
}

void Deck::push(Card&& val)
{
    pile.push(val);
    this->top().setPosition(this->rect.left,this->rect.top);
}

void Deck::pop()
{
    pile.pop();
    if(!this->empty()) this->top().setPosition(this->rect.left,this->rect.top); //jeśli coś jest pod spodem to niech, deck da karcie pod spodem swoją pozycje
}

void Deck::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    
    if(!this->empty()) target.draw(this->top(),states);
    else
        target.draw(frame);
    
    
}

void Deck::clear()
{
    while (!this->empty())
    {
        this->pop();
    }
    
}


sf::FloatRect Deck::get_rect() const
{
    return this->rect;
}