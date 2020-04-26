#include <set>
#include <random>
#include <stdexcept>
#include <iterator>
#include <optional>
#include <SFML/Graphics.hpp>
#include <utility>
#include <initializer_list>
#include <iostream>
#include <thread>
#include <mutex>
#include "player.hpp"
#include "board.hpp"
#include "card.hpp"
#include "move.hpp"
#include "deck.hpp"
#include "server_client.hpp"


class Game: public sf::Drawable
{
    private:

    sf::RenderWindow okno;
    std::mutex game_mutex;

    Player blue_player, red_player;
    Board my_board;
    Player const* whose_turn;   //wskaźnik do consta
    static double scale;
    bool running;
    std::optional<Move> potential_move;
    
    void window_setup();
    bool check_move(const Player* player_pointer, Move& ruch) const; // sprawdza legalność ruchu
    void players_move(Move&); //obsługuje ruch
    
    Player const* get_players_pointer() const;
    Player const* get_opponents_pointer() const;
    static void set_scale(double);

    std::optional<server_client> server_conenction;

    public:

    Game(); //daje początkowo karty na stół i początkową karte z kosza

    static const double get_scale();
    static void load_texuture();
    bool is_running() const;
    void event_handling();
    void clear_and_draw_all();
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

};