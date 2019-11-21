#include"game.hpp"

Game::Game()
{
    player_init(red_player);
    player_init(blue_player);

}

void Game::player_init(Player my_player) //ustawia początkowe karty gracza
{
    std::set<Card> possible_cards;

    for(short i=0; i<4; ++i) //4 iteracje dla każdego koloru
    {
        for(short j=0; j<13; ++j) //13 iteracji dla każdej wartości karty
        {
            Card bufor;
            bufor.kolor=Card::Colour(i);
            bufor.wartosc=Card::Value(j);
            possible_cards.insert(bufor);
        }

    }

    std::default_random_engine generator; //przygotowanie do losowania


    while(!possible_cards.empty())
    {
        std::uniform_int_distribution<int> distribution(0,possible_cards.size());
        int random_num = distribution(generator);
        
        std::set<Card>::iterator it = possible_cards.begin();
        if(random_num>0) std::advance(it,random_num-1); //przesuwa iterator na wybrane miejsce jeżeli nie został wylosowany .begin()

        my_player.deck.push(*it); //dodanie karty na stos gracza (talia)
        possible_cards.erase(it); //usunięcie wykorzystanej karty z drzewa
    }

}
