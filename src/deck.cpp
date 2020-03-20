#include "deck.hpp"
#include "game.hpp"

Deck::Deck(sf::FloatRect prostokat)
:pile(std::list<Card>())
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
    return *(pile.rbegin());
}

const Card& Deck::top() const
{
    return *(pile.rbegin());
}

Card& Deck::begin()
{
    return *(pile.begin());

}

const Card& Deck::begin() const
{
    return *(pile.begin());
}


size_t Deck::size() const
{
    return pile.size();
}

void Deck::push(const Card& val)
{
    pile.push_back(val);
    this->top().setPosition(this->rect.left,this->rect.top);
}

void Deck::push(Card&& val)
{
    pile.push_back(val);
    this->top().setPosition(this->rect.left,this->rect.top);
}

void Deck::pop()
{
    pile.pop_back();
    if(!this->empty()) this->top().setPosition(this->rect.left,this->rect.top); //jeśli coś jest pod spodem to niech, deck da karcie pod spodem swoją pozycje
}

void Deck::pop_front()
{
    pile.pop_front();
}

void Deck::deck_scaling()
{
    rect.left *= Game::scale;
    rect.top *= Game::scale;
    rect.width *= Game::scale;
    rect.height *= Game::scale;

    frame.setPosition({rect.left, rect.top});
    frame.setSize({rect.width, rect.height});

    for(Card& x: pile)
    {
        x.card_scaling();
    }

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