#include"game.hpp"

Game::Game()
{
    //wersja gry za możliwością dania asa na stół przy otwarciu // możeliwe poźniej do zmiany
    //niebieski gracz wypełnia pierwsze cztery pola zewnętrzne a czerwony cztery ostatnie
    for(short i=0; i<8; ++i)
    {
        if(i<4)
        {
            my_board.pola_zew[i].push(blue_player.deck.top());
            blue_player.deck.pop();
        }
        else
        {
            my_board.pola_zew[i].push(red_player.deck.top());
            red_player.deck.pop();
        }
    }

    do //inicjacja koszy do momentu kiedy karty w koszach graczy będą różne
    {
        blue_player.trash.push(blue_player.deck.top());
        blue_player.deck.pop();

        red_player.trash.push(red_player.deck.top());
        red_player.deck.pop();
    } while (blue_player.trash.top().get_value()==red_player.trash.top().get_value()); //jeżeli karty będą miały tą samą wartośc, iteruj
    
    

    if(static_cast<int>(blue_player.trash.top().get_value()) > static_cast<int>(red_player.trash.top().get_value()))//prawdzamy kto ma wyższą karte w koszu, kto zaczyna
    {
        whos_turn=&blue_player; //zaczyna niebieski
    }
    else if(static_cast<int>(blue_player.trash.top().get_value())==static_cast<int>(red_player.trash.top().get_value())) //karty  w koszach równe, dodajemy kolejną
    {
        throw std::runtime_error("Bład w inicjacji koszy");
    }
    else
    {
        whos_turn=&red_player; //zaczyna czerwony
    }
}


void Game::players_move(Player* player_pointer, Board& table)
{
    bool end_of_turn = false; // przyjmie wartość prawda gry gracz odłoży na kupe
    while(!end_of_turn)
    {
        


        
    }
    

}