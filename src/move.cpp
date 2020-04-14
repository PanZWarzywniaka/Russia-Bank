#include"move.hpp"

Move::Move(const std::shared_ptr<Deck> lhs, Card karta)
:skad(lhs),
dokad(nullptr),
karta_w_reku(karta)
{

}

Move::Move(const std::shared_ptr<Deck> lhs, const std::shared_ptr<Deck> rhs, Card&& karta) //karta zostaje zabrana, przejęta i w domyśle zabrana z miejsca w którym była 
:karta_w_reku(karta),
skad(lhs),
dokad(rhs)
{
    if(skad==nullptr) throw std::runtime_error("Move nie ma wzkaźnika skad");
}

const std::shared_ptr<Deck> Move::get_origin() const
{
    return skad;
}

const std::shared_ptr<Deck> Move::get_destination() const
{
    return dokad;
}

const Card Move::get_card() const
{
    return karta_w_reku;
}

void Move::set_destination(std::shared_ptr<Deck> destination)
{
    dokad = destination;
}

void Move::set_cards_position(float x, float y)
{
    karta_w_reku.setPosition(x,y);
}