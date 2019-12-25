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
    else if(static_cast<int>(blue_player.peek_trash_top().get_value())==static_cast<int>(red_player.peek_trash_top().get_value()))//wcześniej musiał być błąd
    {
        throw std::runtime_error("Bład w inicjacji koszy");
    }
    else
    {
        whose_turn=&red_player; //zaczyna czerwony
    }

}

bool Game::players_move(Player* player_pointer,Move& ruch) //sprawdzamy czy ruch jest możliwy   
{
    Player* opponents_pointer = [this](Player* gracz){if(gracz==&blue_player) return &red_player; else return &blue_player;}(player_pointer); //ustawienie wskaźnika na obecnego przeciwnika

    //destynacje dzielimy na kategorie, środek, zewnętrzne, kupa, talia, nasza i przeciwnika

    if(ruch.get_destination()==player_pointer->get_trash_pointer()) //nasza kupa odłożenie karty na kupe->ruch przeciwnika
    {
        player_pointer->push_trash(ruch.get_card()); 
        //zamiana graczy 
        this->whose_turn = opponents_pointer;
        return true;
    }
    else if(ruch.get_destination()==opponents_pointer->get_trash_pointer())//kupa przeciwnika
    {
        int players_card_val = static_cast<int>(ruch.get_card().get_value()); //jezeli karta ma wartość AS, to card_val będzie równy 0, więc można położyć tylko większą
        int opponents_card_val = static_cast<int>(opponents_pointer->peek_trash_top().get_value()); // program nie powinein zgłaszać także wyjątków przy królu bo nie ma karty z card_val==13

        if(players_card_val==++opponents_card_val || players_card_val==--opponents_card_val) //jeżeli karta gracza ma wartość jeden mniejszą lub jeden większą od tego co ma przeciwnik w koszu to dopuszczamy taki ruch
        {
            opponents_pointer->push_trash(ruch.get_card());
            return true;
        }
        else
        {
            return false;
        }
    }
    else if(ruch.get_destination()==player_pointer->get_deck_pointer() || ruch.get_destination()==opponents_pointer->get_deck_pointer())//nasza talia lub talia przeciwnika
    {
        return false; //nie dopuszczamy odłożenia karty do talli
    }
    else //albo bankowa albo zewnętrzna
    {
        std::optional<int> possible_banks_array_addres = [this,ruch]() -> std::optional<int>
        {
            for(int i=0; i<8; ++i)
            {
                if(ruch.get_destination()==&my_board.pola_bank[i])
                {
                    return i;
                }
            }
            return std::nullopt;
        }(); //wywołanie lambdy na koniec

        if(possible_banks_array_addres.has_value()) //jeżeli gracz chce dać karte na strefe bankową
        {
            if(my_board.pola_bank[possible_banks_array_addres.value()].empty()) //jeżeli na konkretnym polu bankowym nic nie ma
            {
                if(ruch.get_card().get_value()==Card::Value::Ace)//a trzymana karta w ręku to AS
                {
                    //tak w tedy dajemy asa na to puste miejsce
                    my_board.pola_bank[possible_banks_array_addres.value()].push(ruch.get_card());
                    return true;
                }
                else //jesli to nie jest as to nara
                {
                    return false;
                }
            }
            else //jeżeli nie jest pusty
            {
                int players_card_val = static_cast<int>(ruch.get_card().get_value());

                //sprawdzamy czy karta którą chcemy połozyć do banku jest tego samego koloru i plus jeden wartości
                if(ruch.get_card().get_colour()==my_board.pola_bank[possible_banks_array_addres.value()].top().get_colour() && ++players_card_val==static_cast<int>(my_board.pola_bank[possible_banks_array_addres.value()].top().get_value()))
                {
                    //jeśli tak w tedy dajemy karte na to miejsce
                    my_board.pola_bank[possible_banks_array_addres.value()].push(ruch.get_card());
                    return true;
                }
                else
                {
                    return false;
                }
            }
            
        }

        std::optional<int> possible_outer_fields_array_addres = [this,ruch]() -> std::optional<int>
        {
            for(int i=0; i<8; ++i)
            {
                if(ruch.get_destination()==&my_board.pola_zew[i])
                {
                    return i;
                }
            }
            return std::nullopt;
        }();

        if(possible_outer_fields_array_addres.has_value()) //jeżeli klikną na strefe zewnątrzną
        {
            if(my_board.pola_zew[possible_outer_fields_array_addres.value()].empty()) //puste pole zew
            {
                my_board.pola_zew[possible_outer_fields_array_addres.value()].push(ruch.get_card()); //na puste miejsce w polach zewnętrznych można położyć każdą karte

                return true;
            }
            else
            {
                int players_card_val = static_cast<int>(ruch.get_card().get_value());

                 //sprawdzamy czy karta jest przeciwnego koloru i czy o jeden mniejsza
                if(ruch.get_card().is_black() ^ my_board.pola_zew[possible_outer_fields_array_addres.value()].top().is_black() && --players_card_val==static_cast<int>(my_board.pola_zew[possible_outer_fields_array_addres.value()].top().get_value()))
                {
                    //jeśli tak w tedy dajemy karte na to miejsce
                    my_board.pola_zew[possible_outer_fields_array_addres.value()].push(ruch.get_card());
                    return true;
                }
                else
                {
                    return false;
                }
                
            }
        }
        else
        {
            //gracz nie klikną na żadne konkretne pole a i tak funkcja zostala wykonana
            throw std::runtime_error("Nie ma takiego ruchu, wszystkie możliwości zostały wyczerpane");
            return false; //czy to jest konieczne?
        }
        
        
    }
    
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