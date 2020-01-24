#include<stack>
#include<set>
#include<random>
#include <SFML/Graphics.hpp>
#include"deck.hpp"

class Player: public sf::Drawable
{
    

    private: //do zmienienia prywatnosc

    Deck my_deck;
    Deck trash;

    std::pair<sf::Vector2u,sf::Vector2u> decks_position;

    public:

    Player(std::pair<sf::Vector2f,sf::Vector2f>); //konstruktor dostaje od game pierwszy dla decku i drugi dla trasha //inicjuje i tasuje talie graczy

    //gettery potrzebne do Game::player_move()
    Deck* get_deck_pointer(); //zwraca wskaźnik do talii
    Deck* get_trash_pointer(); //zwraca wskaźnik do kosza

    Card peek_trash_top() const; //zwraca karte zwierzchu kosza
    Card peek_deck_top() const; //zwraca karte zwierzchu tali

    Card draw_trash(); //zwraca karte zwierzchu kosza i uzuwa z niego
    Card draw_deck(); //zwraca karte zwierzchu tali i uzuwa z niej

    void push_trash(Card&&); //dodaje karte do kosza

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override; //ta funkcja ju nie jest wirtualna ale musimy ja nadpisac

};