#include"game.hpp"

Game::Game()
{
    player_init(red_player);
    player_init(blue_player);
    game_start(blue_player,red_player,my_board);
}

void Game::player_init(Player& my_player) //ustawia początkowe karty gracza
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

void Game::game_start(Player& blue, Player& red, Board& table) //daje początkowo karty na stół i początkową karte z kosza, decyduje kto zaczyna
//wersja gry za możliwością dania asa na stół przy otwarciu // możeliwe poźniej do zmiany
{
    //niebieski gracz wypełnia pierwsze cztery pola zewnętrzne a czerwony cztery ostatnie
    for(short i=0; i<8; ++i)
    {
        if(i<4)
        {
            table.pola_zew[i].push(blue.deck.top());
            blue.deck.pop();
        }
        else
        {
            table.pola_zew[i].push(red.deck.top());
            red.deck.pop();
        }
    }

    do //inicjacja koszy do momentu kiedy karty w koszach graczy będą różne
    {
        blue.trash.push(blue.deck.top());
        blue.deck.pop();

        red.trash.push(red.deck.top());
        red.deck.pop();
    } while (blue.trash.top().wartosc==red.trash.top().wartosc); //jeżeli karty będą miały tą samą wartośc, iteruj
    
    

    if(static_cast<int>(blue.trash.top().wartosc) > static_cast<int>(red.trash.top().wartosc))//prawdzamy kto ma wyższą karte w koszu, kto zaczyna
    {
        whos_turn=&blue; //zaczyna niebieski
    }
    else if(static_cast<int>(blue.trash.top().wartosc)==static_cast<int>(red.trash.top().wartosc)) //karty  w koszach równe, dodajemy kolejną
    {
        throw std::runtime_error("Bład w inicjacji koszy");
    }
    else
    {
        whos_turn=&red; //zaczyna czerwony
    }
}

void Game::players_move(Player* player_pointer, Board& table)
{
    bool end_of_turn = false; // przyjmie wartość prawda gry gracz odłoży na kupe
    while(!end_of_turn)
    {

        
    }
    

}