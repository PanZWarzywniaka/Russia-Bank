#include "deck.hpp"
#include "game.hpp"

Deck::Deck()
:pile(std::list<Card>())
{
    
}

void Deck::initial_setup()
{
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

void Deck::reverse()
{
    pile.reverse();
}

void Deck::deck_scaling(sf::Vector2u position)
{
    rect.left = position.x*Game::get_scale();
    rect.top = position.y*Game::get_scale();
    rect.width = Card::get_default_single_card_size().x*Game::get_scale();
    rect.height = Card::get_default_single_card_size().y*Game::get_scale();

    frame.setPosition({rect.left, rect.top});
    frame.setSize({rect.width, rect.height});

    for(Card& x: pile)
    {
        x.card_scaling(position);
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