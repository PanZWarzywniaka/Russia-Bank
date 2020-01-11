#include<stack>
#include <SFML/Graphics.hpp>
#include"deck.hpp"
class Board
{
    private:

    Deck pola_bank[8]; //trzeba rozważyć czy warto użyć std::vector
    Deck pola_zew[8];

    
    //tekstury

    

    public:

    Board();
    

    friend class Game;
};
