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

    //gettery potrzebne do Game::player_move()
    std::stack<Card>* get_deck_pointer(); //zwraca wskaźnik do talii
    std::stack<Card>* get_trash_pointer(); //zwraca wskaźnik do kosza

    Card peek_trash_top() const; //zwraca karte zwierzchu kosza
    Card peek_deck_top() const; //zwraca karte zwierzchu tali

    Card draw_trash(); //zwraca karte zwierzchu kosza i uzuwa z niego
    Card draw_deck(); //zwraca karte zwierzchu tali i uzuwa z niej

    void push_trash(Card); //dodaje karte do kosza

};