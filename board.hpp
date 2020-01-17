#include<stack>
#include <vector>
#include <SFML/Graphics.hpp>
#include"deck.hpp"
class Board: public sf::Drawable
{
    private:

    Deck pola_bank[8]; 
    Deck pola_zew[8];

    
    //tekstury, jeśli się zdecyduje na obramówki kart

    

    public:

    Board() = delete;
    Board(std::pair<std::vector<sf::Vector2f>,std::vector<sf::Vector2f>>); //pierwszy przechowuje pola bankowe drugi pola zewnetrzne
    
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    friend class Game;
};
