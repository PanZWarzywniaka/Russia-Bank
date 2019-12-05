#include"move.hpp"

Move::Move(const std::stack<Card>* lhs, const std::stack<Card>* rhs, Card&& karta) //karta zostaje zabrana, przejęta i w domyśle zabrana z miejsca w którym była 
{
    karta_w_reku = karta;
    skad = lhs;
    dokad = rhs;
}