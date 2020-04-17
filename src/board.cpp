#include"board.hpp"

Board::Board() //przechowuje pozycje
//pola bank
:pola_bank{ 
            std::shared_ptr<Deck>(new Deck()),
            std::shared_ptr<Deck>(new Deck()),
            std::shared_ptr<Deck>(new Deck()),
            std::shared_ptr<Deck>(new Deck()),
            std::shared_ptr<Deck>(new Deck()),
            std::shared_ptr<Deck>(new Deck()),
            std::shared_ptr<Deck>(new Deck()),
            std::shared_ptr<Deck>(new Deck())
        },
// pola zewnętrzne
pola_zew{
            std::shared_ptr<Deck>(new Deck()),
            std::shared_ptr<Deck>(new Deck()),
            std::shared_ptr<Deck>(new Deck()),
            std::shared_ptr<Deck>(new Deck()),
            std::shared_ptr<Deck>(new Deck()),
            std::shared_ptr<Deck>(new Deck()),
            std::shared_ptr<Deck>(new Deck()),
            std::shared_ptr<Deck>(new Deck())
        }
{

}

std::pair<std::array<std::shared_ptr<Deck>,8>,std::array<std::shared_ptr<Deck>,8>> Board::get_decks_arrays() const
{
    return std::make_pair(pola_bank,pola_zew);
}

void Board::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for(size_t i=0; i<8; ++i)
    {
        target.draw(*pola_bank[i],states);
    }

    for(size_t i=0; i<8; ++i)
    {
        target.draw(*pola_zew[i],states);
    }
}
