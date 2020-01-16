#include <set>
#include <random>
#include <stdexcept>
#include <iterator>
#include <optional>
#include <SFML/Graphics.hpp>
#include"player.hpp"
#include"board.hpp"
#include"card.hpp"
#include"move.hpp"
#include"deck.hpp"
#include<utility>
#include<initializer_list>

class Game
{
    private:

    Player blue_player, red_player;
    Board my_board;
    Player* whose_turn;

    public:

    sf::RenderWindow okno;
    static float scale;

    Game(); //daje początkowo karty na stół i początkową karte z kosza
    const Deck* get_clicked_Deck_pointer(sf::Event) const;
    bool players_move(Player*, Move&); //funkcja obsugująca pojedynczy ruch przeniesienie karty i sprawdzanie czy ruch jest dozwolony, zwraca true jeśli się ruch udał
    //gettery
    Player* get_whose_turn() const;
    Board& get_board();

};