#include"move.hpp"

Move::Move(const Deck* lhs, const Deck* rhs, Card&& karta) //karta zostaje zabrana, przejęta i w domyśle zabrana z miejsca w którym była 
:karta_w_reku(karta)
{
    if(skad==nullptr || dokad==nullptr) throw std::runtime_error("Move nie ma wzkaźników miejsca");
    skad = lhs;
    dokad = rhs;
}

const Deck* Move::get_origin() const
{
    return skad;
}

const Deck* Move::get_destination() const
{
    return dokad;
}

Card Move::get_card() const
{
    return karta_w_reku;
}