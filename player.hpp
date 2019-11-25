#include<stack>
#include<set>
#include<random>
#include"card.hpp"

class Player
{
    

    private: //do zmienienia prywatnosc

    std::stack<Card> deck;
    std::stack<Card> trash;

    public:

    Player(); //konstruktor domyślny
    Card peek_trash_top() const;
    Card peek_deck_top() const;

    void push_trash(Card);
    Card draw_trash();
    Card draw_deck();
};