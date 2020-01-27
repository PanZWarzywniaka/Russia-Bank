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

class Game: public sf::Drawable
{
    private:

    Player blue_player, red_player;
    Board my_board;
    Player* whose_turn;

    public:

    sf::RenderWindow okno;
    static float scale;

    Game(); //daje początkowo karty na stół i początkową karte z kosza
    bool players_move(Player*, Move&); //funkcja obsugująca pojedynczy ruch przeniesienie karty i sprawdzanie czy ruch jest dozwolony, zwraca true jeśli się ruch udał
    //gettery
    Player* get_players_pointer() const;
    Player* get_opponents_pointer(); //ta funkcja powinna być const ale nie moge tam tego wsadzić

    Board& get_board();

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

};