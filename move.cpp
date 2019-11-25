#include"move.hpp"

Move::Move()
{
    skad=nullptr;
    dokad=nullptr;
}

Move::Move(std::unique_ptr<std::stack<Card>> first, std::unique_ptr<std::stack<Card>> second)
:skad(first),
dokad(second)
{
    
}