#include"move.hpp"

Move::Move()
{
    skad=nullptr;
    dokad=nullptr;
}

Move::Move(std::unique_ptr<std::stack<Card>> first, std::unique_ptr<std::stack<Card>> second)
:skad(std::move(first)),
dokad(std::move(second)) //bez tego nie działa niewadomo czemu XD
{
    
}