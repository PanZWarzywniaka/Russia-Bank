#include<stack>
#include"card.hpp"
class Board
{
    private: //do zmiany

    std::stack<Card> pola_bank[8]; //trzeba rozważyć czy warto użyć std::vector
    std::stack<Card> pola_zew[8];

    public:

    Board();

    friend class Game;
};
