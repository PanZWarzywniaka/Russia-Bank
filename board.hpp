#include<stack>
#include"card.hpp"
class Board
{
    private:

    std::stack<Card> pola_bank[8];
    std::stack<Card> pola_zew[8];

    public:
    
    Board();

};
