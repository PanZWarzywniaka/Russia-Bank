#include"game.hpp"

Game::Game()
:okno(sf::VideoMode(800, 600), "Garibaldka 0.1")
{
    okno.setFramerateLimit(60); //limit fps 60

    //wersja gry za możliwością dania asa na stół przy otwarciu // możeliwe poźniej do zmiany
    //niebieski gracz wypełnia pierwsze cztery pola zewnętrzne a czerwony cztery ostatnie
    for(short i=0; i<8; ++i)
    {
        if(i<4)
        {
            my_board.pola_zew[i].push(blue_player.draw_deck());
            //blue_player.deck.pop();
        }
        else
        {
            my_board.pola_zew[i].push(red_player.draw_deck());
            //red_player.deck.pop();
        }
    }

    do //inicjacja koszy do momentu kiedy karty w koszach graczy będą różne
    {
        blue_player.push_trash(blue_player.draw_deck());
        red_player.push_trash(red_player.draw_deck());
    } while (blue_player.peek_trash_top().get_value()==red_player.peek_trash_top().get_value()); //jeżeli karty będą miały tą samą wartośc, iteruj
    
    

    if(static_cast<int>(blue_player.peek_trash_top().get_value()) > static_cast<int>(red_player.peek_trash_top().get_value()))//prawdzamy kto ma wyższą karte w koszu, kto zaczyna
    {
        whose_turn=&blue_player; //zaczyna niebieski
    }
    else if(static_cast<int>(blue_player.peek_trash_top().get_value())==static_cast<int>(red_player.peek_trash_top().get_value())) //karty  w koszach równe, dodajemy kolejną
    {
        throw std::runtime_error("Bład w inicjacji koszy");
    }
    else
    {
        whose_turn=&red_player; //zaczyna czerwony
    }

}


void Game::players_turn(Player* player_pointer, Board& table)
{
    bool end_of_turn = false; // przyjmie wartość prawda gry gracz odłoży na kupe
    Player* opponent_pointer = [this](Player* gracz){if(gracz==&blue_player) return &red_player; else return &blue_player;}(player_pointer); //ustawienie wskaźnika na obecnego przeciwnika
    while(!end_of_turn)
    {
        std::stack<Card>* players_card_pick=nullptr; //wskaźnik stosu z którego bierzemy
        std::stack<Card>* players_card_destination=nullptr; //wskaźnik stosu do którego dajemy
        
        //do zrobienia jak bedze okno
        //tu będzie konstuowany obiekt Move dla gracza
        //i przekazywany do players_move


        
    }
    

}

bool Game::players_move(Move& ruch)
{


}

//gettery

Player* Game::get_whose_turn() const
{
    if(whose_turn!=nullptr)
    {
        return whose_turn;
    }
    else
    {
        throw std::runtime_error("Error: Nie wiadomo czyja tura");
    }
}

Board& Game::get_board()
{
    return my_board;
}