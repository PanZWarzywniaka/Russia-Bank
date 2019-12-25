#include"move.hpp"

Move::Move(const std::stack<Card>* lhs, const std::stack<Card>* rhs, Card&& karta) //karta zostaje zabrana, przejęta i w domyśle zabrana z miejsca w którym była 
{
    if(skad==nullptr || dokad==nullptr) throw std::runtime_error("Move nie ma wzkaźników miejsca");
    karta_w_reku = karta;
    skad = lhs;
    dokad = rhs;
}

const std::stack<Card>* Move::get_origin() const
{
    return skad;
}

const std::stack<Card>* Move::get_destination() const
{
    return dokad;
}

Card Move::get_card() const
{
    return karta_w_reku;
}