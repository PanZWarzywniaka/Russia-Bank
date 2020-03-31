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
#include"server_client.hpp"
#include<utility>
#include<initializer_list>
#include<iostream>


class Game: public sf::Drawable
{
    private:

    Player blue_player, red_player;
    Board my_board;
    Player const* whose_turn;   //wskaźnik do consta
    std::optional<server_client> server_conenction;

    bool check_move(const Player* player_pointer, Move& ruch) const; // sprawdza legalność ruchu


    public:

    sf::RenderWindow okno;
    static float scale;

    Game(); //daje początkowo karty na stół i początkową karte z kosza
    void players_move(Move&); //obsługuje ruch
    void window_scaling(); //to be implemented
    //gettery
    Player const* get_players_pointer() const;
    Player const* get_opponents_pointer() const;
    Board& get_board();

    void clear_and_draw_all(const std::optional<Card>& taken_card);
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

};