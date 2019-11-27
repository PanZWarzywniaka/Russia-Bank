#include"move.hpp"

/*
Move::Move()
{
    skad=nullptr;
    dokad=nullptr;
}
*/

Move::Move( const std::stack<Card>* lhs, const std::stack<Card>* rhs,Card&& kloc)
{
    karta_w_reku = kloc;
    skad = lhs;
    dokad = rhs;
}