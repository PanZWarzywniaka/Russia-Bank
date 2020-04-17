#include <stack>
#include <vector>
#include <array>
#include <memory>
#include <SFML/Graphics.hpp>
#include"deck.hpp"
class Board: public sf::Drawable
{
    private:

    std::array<std::shared_ptr<Deck>,8> pola_bank;
    std::array<std::shared_ptr<Deck>,8> pola_zew;

    public:
    Board();
    std::pair<std::array<std::shared_ptr<Deck>,8>,std::array<std::shared_ptr<Deck>,8>> get_decks_arrays() const;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    friend class Game;
};
