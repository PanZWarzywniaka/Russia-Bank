#include"board.hpp"

Board::Board(std::pair<std::vector<sf::Vector2f>,std::vector<sf::Vector2f>> pos_pair) //przechowuje pozycje
//pola bank
:pola_bank[0](sf::FloatRect(pos_pair.first[0],sf::Vector2f(Card::single_card_size))),
:pola_bank[1](sf::FloatRect(pos_pair.first[1],sf::Vector2f(Card::single_card_size))),
:pola_bank[2](sf::FloatRect(pos_pair.first[2],sf::Vector2f(Card::single_card_size))),
:pola_bank[3](sf::FloatRect(pos_pair.first[3],sf::Vector2f(Card::single_card_size))),
:pola_bank[4](sf::FloatRect(pos_pair.first[4],sf::Vector2f(Card::single_card_size))),
:pola_bank[5](sf::FloatRect(pos_pair.first[5],sf::Vector2f(Card::single_card_size))),
:pola_bank[6](sf::FloatRect(pos_pair.first[6],sf::Vector2f(Card::single_card_size))),
:pola_bank[7](sf::FloatRect(pos_pair.first[7],sf::Vector2f(Card::single_card_size))),
// pola zewnętrzne
:pola_zew[0](sf::FloatRect(pos_pair.first[0],sf::Vector2f(Card::single_card_size))),
:pola_zew[1](sf::FloatRect(pos_pair.first[1],sf::Vector2f(Card::single_card_size))),
:pola_zew[2](sf::FloatRect(pos_pair.first[2],sf::Vector2f(Card::single_card_size))),
:pola_zew[3](sf::FloatRect(pos_pair.first[3],sf::Vector2f(Card::single_card_size))),
:pola_zew[4](sf::FloatRect(pos_pair.first[4],sf::Vector2f(Card::single_card_size))),
:pola_zew[5](sf::FloatRect(pos_pair.first[5],sf::Vector2f(Card::single_card_size))),
:pola_zew[6](sf::FloatRect(pos_pair.first[6],sf::Vector2f(Card::single_card_size))),
:pola_zew[7](sf::FloatRect(pos_pair.first[7],sf::Vector2f(Card::single_card_size)))
{

}