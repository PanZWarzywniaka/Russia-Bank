#include "player.hpp"


Player::Player(std::pair<sf::Vector2f, sf::Vector2f> pos) //inicjuje i tasuje talie graczy //pierwszy wektor pos dla decku drugi dla trasha
:my_deck(new Deck(sf::FloatRect(pos.first,Card::actual_single_card_size))),
trash(new Deck(sf::FloatRect(pos.second,Card::actual_single_card_size)))
{
    std::set<Card> possible_cards;

    for(short i=0; i<4; ++i) //4 iteracje dla każdego koloru
    {
        for(short j=0; j<13; ++j) //13 iteracji dla każdej wartości karty
        {
            Card bufor(static_cast<Card::Value>(j), static_cast<Card::Colour>(i));
            possible_cards.insert(bufor);
        }

    }

    std::default_random_engine generator(std::chrono::high_resolution_clock::now().time_since_epoch().count()); //przygotowanie do losowania


    while(!possible_cards.empty())
    {
        std::uniform_int_distribution<int> distribution(0,possible_cards.size()-1);
        int random_num = distribution(generator);
        
        std::set<Card>::iterator it = possible_cards.begin();
        std::advance(it,random_num); //przesuwa iterator na wybrane miejsce jeżeli nie został wylosowany .begin()

        this->my_deck->push(*it); //dodanie karty na stos gracza (talia)
        possible_cards.erase(it); //usunięcie wykorzystanej karty z drzewa
    }
    
}

std::shared_ptr<Deck> Player::get_deck_pointer()
{
    return my_deck;
}

std::shared_ptr<Deck> Player::get_trash_pointer()
{
    return trash;
}

Card Player::peek_trash_top() const
{
    return trash->top();
}
Card Player::peek_deck_top() const
{
    return my_deck->top();
}
void Player::push_trash(Card&& crd)
{
    trash->push(crd);
}

Card Player::draw_trash()
{
    if(trash->empty()) throw std::runtime_error("Player's trash is empty! Unable to draw");
    auto ret = trash->top();
    trash->pop();
    return ret;
}

Card Player::draw_deck()
{
    if(my_deck->empty()) throw std::runtime_error("Player's deck is empty! Unable to draw");
    auto ret = my_deck->top();
    my_deck->pop();
    return ret;
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(*this->my_deck,states);
    target.draw(*this->trash,states);
}