#include "deck.hpp"
#include "game.hpp"

Deck::Deck(Type typ)
:pile(std::list<Card>())
{
    type = typ;
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

void Deck::push(const Card& crd)
{
    pile.push_back(crd);
    switch (type)
    {
        case Type::trash:
        {
            top().setPosition(rect.left,rect.top);
            std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
            std::uniform_real_distribution<float> distributor(-15,15);
            top().setRotation(distributor(generator));

            break;
        }
        //case Type::outer:
    
        default:
        {
            top().setPosition(rect.left,rect.top);
            break;
        }
    }
}

void Deck::push(Card&& crd)
{
    pile.push_back(crd);
    switch (type)
    {
        case Type::trash:
        {
            top().setPosition(rect.left,rect.top);
            std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
            std::uniform_real_distribution<float> distributor(-15,15);
            top().setRotation(distributor(generator));

            break;
        }
        //case Type::outer:
    
        default:
        {
            top().setPosition(rect.left,rect.top);
            break;
        }
    }
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
    
    if(!this->empty())
    {
        if(type==Deck::Type::trash) // jeżeli rysujemy kosz to rysujemy, to rysujemy wszystkie karty pod spodem
        {
            for(auto it = pile.begin(); it!=pile.end(); ++it)
            {
                target.draw(*it,states);
            }
        }
        else //jeśli każdy inny deck, to rysujemy  tylko karte z wierzchu
        {
            target.draw(top(),states);
        }
    } 
    else
    {
        target.draw(frame);
    }
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