#include<stack>
#include <vector>
#include <SFML/Graphics.hpp>
#include"deck.hpp"
class Board
{
    private:

    Deck pola_bank[8]; 
    Deck pola_zew[8];

    
    //tekstury, jeśli się zdecyduje na obramówki kart

    

    public:

    Board() = delete;
    Board(std::pair<std::vector<sf::Vector2f>,std::vector<sf::Vector2f>>); //pierwszy przechowuje pola bankowe drugi pola zewnetrzne
    

    friend class Game;
};
