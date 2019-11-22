#include<stack>
#include"card.hpp"

class Player
{
    

    public: //do zmienienia prywatnosc

    std::stack<Card> deck;
    std::stack<Card> trash;

    Player(); //konstruktor domyślny
};