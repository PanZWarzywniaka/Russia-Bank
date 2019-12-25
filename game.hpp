#include <set>
#include <random>
#include <stdexcept>
#include <iterator>
#include <SFML/Graphics.hpp>
#include"player.hpp"
#include"board.hpp"
#include"card.hpp"
#include"move.hpp"

class Game
{
    private:

    Player blue_player, red_player;
    Board my_board;
    Player* whose_turn;

    public:

    sf::RenderWindow okno;

    Game(); //daje początkowo karty na stół i początkową karte z kosza
    //jeszce nie wiem czy będzie potrzebna void players_turn(Player*, Board&); //funckja obsługująca ruchy gracza, do momentu zakończenia tury
    bool players_move(Player*, Move&); //funkcja obsugująca pojedynczy ruch przeniesienie karty i sprawdzanie czy ruch jest dozwolony, zwraca true jeśli się udał
    //gettery
    Player* get_whose_turn() const;
    Board& get_board();

};