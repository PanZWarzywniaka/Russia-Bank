#include"board.hpp"

Board::Board(std::pair<std::vector<sf::Vector2f>,std::vector<sf::Vector2f>> pos_pair) //przechowuje pozycje
//pola bank
:pola_bank{ 
            (sf::FloatRect(pos_pair.first[0],sf::Vector2f(Card::actual_single_card_size))),
            (sf::FloatRect(pos_pair.first[1],sf::Vector2f(Card::actual_single_card_size))),
            (sf::FloatRect(pos_pair.first[2],sf::Vector2f(Card::actual_single_card_size))),
            (sf::FloatRect(pos_pair.first[3],sf::Vector2f(Card::actual_single_card_size))),
            (sf::FloatRect(pos_pair.first[4],sf::Vector2f(Card::actual_single_card_size))),
            (sf::FloatRect(pos_pair.first[5],sf::Vector2f(Card::actual_single_card_size))),
            (sf::FloatRect(pos_pair.first[6],sf::Vector2f(Card::actual_single_card_size))),
            (sf::FloatRect(pos_pair.first[7],sf::Vector2f(Card::actual_single_card_size)))
        },
// pola zewnętrzne
pola_zew{
            (sf::FloatRect(pos_pair.second[0],sf::Vector2f(Card::actual_single_card_size))),
            (sf::FloatRect(pos_pair.second[1],sf::Vector2f(Card::actual_single_card_size))),
            (sf::FloatRect(pos_pair.second[2],sf::Vector2f(Card::actual_single_card_size))),
            (sf::FloatRect(pos_pair.second[3],sf::Vector2f(Card::actual_single_card_size))),
            (sf::FloatRect(pos_pair.second[4],sf::Vector2f(Card::actual_single_card_size))),
            (sf::FloatRect(pos_pair.second[5],sf::Vector2f(Card::actual_single_card_size))),
            (sf::FloatRect(pos_pair.second[6],sf::Vector2f(Card::actual_single_card_size))),
            (sf::FloatRect(pos_pair.second[7],sf::Vector2f(Card::actual_single_card_size)))
        }
{

}

std::pair<std::array<Deck,8>,std::array<Deck,8>> Board::get_decks_arrays() const
{
    return std::make_pair(pola_bank,pola_zew);
}

void Board::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for(size_t i=0; i<8; ++i)
    {
        target.draw(pola_bank[i],states);
    }

    for(size_t i=0; i<8; ++i)
    {
        target.draw(pola_zew[i],states);
    }
}