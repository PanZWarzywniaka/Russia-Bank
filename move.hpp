#include"card.hpp"
#include<memory>

class Move
{
private:
    std::unique_ptr<std::stack<Card>> skad; //skąd bierzemy karte
    std::unique_ptr<std::stack<Card>>  dokad;
public:

    Move();
    Move(std::unique_ptr<std::stack<Card>> , std::unique_ptr<std::stack<Card>>);

};
