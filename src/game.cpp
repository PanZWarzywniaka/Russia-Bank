#include"game.hpp"

float Game::scale = 1;

Game::Game()
:okno(sf::VideoMode(1000, 1000), "Garibaldka 0.1"),
blue_player(std::make_pair(sf::Vector2f(290,20), sf::Vector2f(610,20))), //pierwszy dla decka drugi dla decka drugi dla trasha
red_player(std::make_pair(sf::Vector2f(290,830), sf::Vector2f(610,830))),
my_board(std::make_pair<std::vector<sf::Vector2f>,std::vector<sf::Vector2f>> /*std::pair<std::vector<sf::Vector2f>,std::vector<sf::Vector2f>>*/
        (
            {
                {390,180},{390,340},{390,500},{390,660}, /*lewa kolumna bakowych*/
                {510,180},{510,340},{510,500},{510,660} /*prawa kolumna bakowych*/
            },
            {
                {240,180},{240,340},{240,500},{240,660}, /*lewa kolumna zewnetrznych*/
                {660,180},{660,340},{660,500},{660,660} /*prawa kolumna zewnetrznych*/
            }
        )
    )
{
    okno.setFramerateLimit(60); //limit fps 60
    scale = 1;

    //wersja gry za możliwością dania asa na stół przy otwarciu // możeliwe poźniej do zmiany
    //niebieski gracz wypełnia pierwsze cztery pola zewnętrzne a czerwony cztery ostatnie
    for(short i=0; i<8; ++i)
    {
        if(i<4)
        {
            my_board.pola_zew[i]->push(blue_player.draw_deck());
        }
        else
        {
            my_board.pola_zew[i]->push(red_player.draw_deck());
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

bool Game::check_move(const Player* player_pointer, Move& ruch) const //sprawdzamy czy ruch jest możliwy   
{
    const Player* opponents_pointer = get_opponents_pointer();
    //destynacje dzielimy na kategorie, środek, zewnętrzne, kupa, talia, nasza i przeciwnika
    if(ruch.get_destination()==ruch.get_origin() || ruch.get_destination()==nullptr)
    {
        return false;
    }
    else if(ruch.get_destination().get()==player_pointer->get_trash_pointer().get()) //nasza kupa odłożenie karty na kupe->ruch przeciwnika
    {
        //zamiana graczy 
        return true;
    }
    else if(ruch.get_destination().get()==opponents_pointer->get_trash_pointer().get())//kupa przeciwnika
    {
        int players_card_val = static_cast<int>(ruch.get_card().get_value()); //jezeli karta ma wartość AS, to card_val będzie równy 0, więc można położyć tylko większą
        int opponents_card_val = static_cast<int>(opponents_pointer->peek_trash_top().get_value()); // program nie powinein zgłaszać także wyjątków przy królu bo nie ma karty z card_val==13

        if(players_card_val==++opponents_card_val || players_card_val==--opponents_card_val) //jeżeli karta gracza ma wartość jeden mniejszą lub jeden większą od tego co ma przeciwnik w koszu to dopuszczamy taki ruch
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if(ruch.get_destination().get()==player_pointer->get_deck_pointer().get() || ruch.get_destination().get()==opponents_pointer->get_deck_pointer().get())//nasza talia lub talia przeciwnika
    {
        return false; //nie dopuszczamy odłożenia karty do talli
    }
    else //albo bankowa albo zewnętrzna
    {
        std::optional<int> possible_banks_array_addres = [this,ruch]() -> std::optional<int>
        {
            for(int i=0; i<8; ++i)
            {
                if(ruch.get_destination()==my_board.pola_bank[i])
                {
                    return i;
                }
            }
            return std::nullopt;
        }(); //wywołanie lambdy na koniec

        if(possible_banks_array_addres.has_value()) //jeżeli gracz chce dać karte na strefe bankową
        {
            if(my_board.pola_bank[possible_banks_array_addres.value()]->empty()) //jeżeli na konkretnym polu bankowym nic nie ma
            {
                if(ruch.get_card().get_value()==Card::Value::Ace)//a trzymana karta w ręku to AS
                {
                    //tak w tedy dajemy asa na to puste miejsce
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
                if(ruch.get_card().get_colour()==my_board.pola_bank[possible_banks_array_addres.value()]->top().get_colour() && --players_card_val==static_cast<int>(my_board.pola_bank[possible_banks_array_addres.value()]->top().get_value()))
                {
                    //jeśli tak w tedy dajemy karte na to miejsce
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
                if(ruch.get_destination().get()==my_board.pola_zew[i].get())
                {
                    return i;
                }
            }
            return std::nullopt;
        }();

        if(possible_outer_fields_array_addres.has_value()) //jeżeli klikną na strefe zewnątrzną
        {
            if(my_board.pola_zew[possible_outer_fields_array_addres.value()]->empty()) //puste pole zew
            {
                //na puste miejsce w polach zewnętrznych można położyć każdą karte
                return true;
            }
            else
            {
                int players_card_val = static_cast<int>(ruch.get_card().get_value());

                 //sprawdzamy czy karta jest przeciwnego koloru i czy o jeden mniejsza
                if(ruch.get_card().is_black() ^ my_board.pola_zew[possible_outer_fields_array_addres.value()]->top().is_black() && ++players_card_val==static_cast<int>(my_board.pola_zew[possible_outer_fields_array_addres.value()]->top().get_value()))
                {
                    //jeśli tak w tedy dajemy karte na to miejsce
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

void Game::players_move(Move& ruch)
{
    if(this->check_move(this->get_players_pointer(),ruch))
    {
        ruch.get_destination()->push(ruch.get_card());
        std::cout<<"Ruch pomyślny "<<ruch.get_card()<<"\n"; 
    }
    else //karta została puszczona ale źle, nie na żaden deck, została położona na tle, cofamy ruch
    {
        ruch.get_origin()->push(ruch.get_card());
        std::cout<<"Ruch zabroniony "<<ruch.get_card()<<"\n";   
    }

    //event handling

    if(ruch.get_destination().get()==this->get_players_pointer()->get_trash_pointer().get()) //jeżeli odłożyliśmy do siebie to zamiana tury
        this->whose_turn = this->get_opponents_pointer();

    if(this->get_players_pointer()->get_deck_pointer()->empty()) //karta na górze kosza, staje się koszem, kosz obracamy i staje się dekiem
    {//to rozwiązanie jest lepsze niż zmiana konstów
        if(whose_turn==&blue_player)
            blue_player.take_trash_and_rotate();
        else
            red_player.take_trash_and_rotate();
    }
        
    if(this->get_players_pointer()->get_trash_pointer()->empty()) //
    {//to rozwiązanie jest lepsze niż zmiana konstów
        std::cout<<"Empty trash handling \n";
        if(whose_turn==&blue_player)
            blue_player.empty_trash_handle();
        else
            red_player.empty_trash_handle();
    }

}


//gettery

Player const* Game::get_players_pointer() const
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

Player const*  Game::get_opponents_pointer() const
{
    if(whose_turn!=nullptr)
    {
        Player const* opponents_pointer = [&](Player const* gracz){if(gracz==&blue_player) return &red_player; else return &blue_player;}(whose_turn); //ustawienie wskaźnika na obecnego przeciwnika
        return opponents_pointer;
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

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(blue_player,states);
    target.draw(red_player,states);
    target.draw(my_board,states);
}

void Game::window_scaling()
{
    blue_player.player_scaling();
    red_player.player_scaling();
    //my_board.board_scaling();
}