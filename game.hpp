#include <set>
#include <random>
#include <iterator>
#include"player.hpp"
#include"board.hpp"
#include"card.hpp"

class Game
{
    private:

    Player blue_player, red_player;
    Board my_board;

    public:

    Game();
    void player_init(Player); //inicjuje i tasuje talje graczy


};