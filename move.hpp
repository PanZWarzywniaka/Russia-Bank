#include"card.hpp"
#include<memory>

class Move
{
private:
    const std::stack<Card>* skad; //skąd bierzemy karte
    const std::stack<Card>*  dokad;
    Card karta_w_reku;
public:

    Move() = delete;
    Move( const std::stack<Card>*, const std::stack<Card>*,Card&&);

};
