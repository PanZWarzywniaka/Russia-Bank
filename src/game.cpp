#include"game.hpp"

double Game::scale = 1;

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
    running = true;

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
        //event handling

        if(server_conenction) 
        {
            //to be implemented
        }
        else
        {
            if(ruch.get_destination().get()==this->get_players_pointer()->get_trash_pointer().get()) //jeżeli odłożyliśmy do siebie to zamiana tury
            {
                std::cout<<"\nZmiana tury!\nTeraz gra ";
                this->whose_turn = this->get_opponents_pointer();
                if(whose_turn==&blue_player)
                    std::cout<<"niebieski\n\n";
                else
                    std::cout<<"czerwony\n\n";
            }
                

            if(this->get_players_pointer()->get_deck_pointer()->empty()) //karta na górze kosza, staje się koszem, kosz obracamy i staje się dekiem
            {
                std::cout<<"\nPusta talia!\n";
                if(whose_turn==&blue_player)
                    blue_player.take_trash_and_rotate();
                else
                    red_player.take_trash_and_rotate();
            }
                
            if(this->get_players_pointer()->get_trash_pointer()->empty()) //wyciągnięcie karty z pod spodu decku i dodanie ją do kosza
            {
                std::cout<<"\nPusty kosz!\n";
                if(whose_turn==&blue_player)
                    blue_player.empty_trash_handle();
                else
                    red_player.empty_trash_handle();
            }
        }
        
    }
    else //karta została puszczona ale źle lub została położona na tle, cofamy ruch
    {
        ruch.get_origin()->push(ruch.get_card());
        std::cout<<"Ruch zabroniony "<<ruch.get_card()<<"\n";   
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

void Game::clear_and_draw_all()
{   
    std::lock_guard my_lock(game_mutex);

    okno.clear(sf::Color::Green);
    okno.draw(*this);

    if(potential_move)
        { 
            const Card& card = potential_move.value().get_card();
            okno.draw(card);
        }
        
    okno.display();
}

const double Game::get_scale()
{
    return Game::scale;
}

void Game::set_scale(double new_scale)
{
    Game::scale = new_scale;
}

void Game::window_scaling()
{
    //skalowanie blue playera (290,20), (610,20)
    blue_player.get_deck_pointer()->deck_scaling({290,20}); 
    blue_player.get_deck_pointer()->deck_scaling({610,20});

    //skalowanie red playera (290,830), (610,830)
    red_player.get_deck_pointer()->deck_scaling({290,830}); 
    red_player.get_deck_pointer()->deck_scaling({610,830});
    
    //skalowanie lewa kolumna bakowych {390,180},{390,340},{390,500},{390,660}
    my_board.pola_bank[0]->deck_scaling({390,180});
    my_board.pola_bank[1]->deck_scaling({390,340});
    my_board.pola_bank[2]->deck_scaling({390,500});
    my_board.pola_bank[3]->deck_scaling({390,660});

    //skalowanie prawa kolumna bakowych {510,180},{510,340},{510,500},{510,660}
    my_board.pola_bank[4]->deck_scaling({510,180});
    my_board.pola_bank[5]->deck_scaling({510,340});
    my_board.pola_bank[6]->deck_scaling({510,500});
    my_board.pola_bank[7]->deck_scaling({510,660});

    //skalowanie lewa kolumna zewnetrznych {240,180},{240,340},{240,500},{240,660} 
    my_board.pola_zew[0]->deck_scaling({240,180});
    my_board.pola_zew[1]->deck_scaling({240,340});
    my_board.pola_zew[2]->deck_scaling({240,500});
    my_board.pola_zew[3]->deck_scaling({240,660});

    //skalowanie prawa kolumna zewnetrznych {660,180},{660,340},{660,500},{660,660}
    my_board.pola_zew[4]->deck_scaling({660,180});
    my_board.pola_zew[5]->deck_scaling({660,340});
    my_board.pola_zew[6]->deck_scaling({660,500});
    my_board.pola_zew[7]->deck_scaling({660,660});

}

bool Game::is_running() const
{
    return running;
}

void Game::event_handling()
{
    std::lock_guard<std::mutex> lock(game_mutex);
    sf::Event event;

    while (okno.pollEvent(event))
    {
            switch (event.type)
            {
            case sf::Event::Closed:
                {
                    okno.close();
                    running = false;
                    break;
                }
            case sf::Event::Resized:
                {   
                    /*
                    static std::chrono::system_clock::time_point lastresize;
                    static std::mutex lr_mut;

                    lr_mut.lock();
                    lastresize = std::chrono::system_clock::now();
                    lr_mut.unlock();

                    sf::Event::SizeEvent size = event.size;
                    unsigned int edge = std::min(size.height,size.width);
                    while(edge%32!=0) edge--;

                    auto defer_resize = [this](std::chrono::system_clock::time_point& lastresize, std::mutex& lr_mut, unsigned int edge)
                    {

                        lr_mut.lock();
                        std::chrono::system_clock::time_point invoke_time = lastresize;
                        lr_mut.unlock();

                        std::this_thread::sleep_for(std::chrono::milliseconds(100)); //the time

                        lr_mut.lock();
                        std::chrono::system_clock::time_point final_time = lastresize;
                        lr_mut.unlock();

                        if(invoke_time == final_time) //make sure that the last window resize happened 200ms ago in order to prevent the window from not maintaining its' aspect ratio 
                        {
                                //OKNO
                            //std::lock_guard my_lock(game_mutex); //prevent raid with drawing
                            okno.setSize({edge,edge});
                            sf::View new_view;
                            new_view.setSize(edge,edge);
                            new_view.setCenter(edge/2,edge/2);
                            okno.setView(new_view);
                                //GRA
                            set_scale(static_cast<double>(edge)/1000); //ustawienie odpowiedniej skali
                            window_scaling();
                            
                        }

                    };

                    std::thread defer_thread(defer_resize,std::ref(lastresize),std::ref(lr_mut),edge);
                    defer_thread.detach();

                    /*
                    STARY KOD 

                    //set scale
                    auto new_size = event.size; //sf::Event::Sizeevent
                    sf::Vector2u win_size = {std::min(new_size.height,new_size.width),std::min(new_size.height,new_size.width)};
                    
                    Game::scale = win_size.x/1000; //to działa tylko w tedy gdy skala 1 = winsize{1000,1000}
                    gra.okno.setSize(win_size);
                    gra.okno.setView(gra.okno.getDefaultView());
                    //gra.window_scaling(); //seting up window according to scale 
                    //gra.clear_and_draw_all(taken_card); //nie wiem czemu ta linijka powoduje błąd wiec lepiej ją wykomentować jak jest niepotrzebna */
                    break;
                }
            case sf::Event::MouseButtonPressed:
                {
                    
                    
                    auto get_origin_and_taken_card = [&]() -> std::optional<std::pair<std::shared_ptr<Deck>,Card>> /*tu odbywa się walidacja skąd możemy zabrać karte*/ 
                    {
                        
                        auto get_card_and_set_its_pos = [&](const std::shared_ptr<Deck> deck) -> Card 
                        {
                            Card buf = deck->top();
                            deck->pop();
                            buf.setPosition(event.mouseButton.x-(Card::actual_single_card_size.x/2),event.mouseButton.y-(Card::actual_single_card_size.y/2));
                            return buf;
                        };

                        sf::Vector2f point (event.mouseButton.x,event.mouseButton.y);

                        for(const std::shared_ptr<Deck> deck: my_board.get_decks_arrays().first) //pola bankowe sprawdzamy, nigdy nie można wziąć karty z banku
                        {   
                            if(deck->get_rect().contains(point))
                            {
                                return std::nullopt;
                            }
                            
                        }

                        for(const std::shared_ptr<Deck> deck: my_board.get_decks_arrays().second) //pola zew sprawdzamy, zawsze można wziąć karty
                        {
                            if(!deck->empty())
                            {
                                if(deck->get_rect().contains(point))
                                {
                                    return std::make_pair(deck,get_card_and_set_its_pos(deck));
                                }
                            }
                        }

                        if(!whose_turn->get_deck_pointer()->empty()) //deck gracza zawsze można
                        {
                            if(whose_turn->get_deck_pointer()->get_rect().contains(point))
                            {
                                const std::shared_ptr<Deck> deck = whose_turn->get_deck_pointer();
                                return std::make_pair(deck,get_card_and_set_its_pos(deck));
                            } 
                           
                        }
            
                        if(!whose_turn->get_trash_pointer()->empty())
                        {
                            if(whose_turn->get_trash_pointer()->get_rect().contains(point)) 
                            {
                                const std::shared_ptr<Deck> deck = whose_turn->get_trash_pointer();
                                return std::make_pair(deck,get_card_and_set_its_pos(deck));
                            }
                        }
                        
                        return std::nullopt;
                    }();

                    if(get_origin_and_taken_card)  
                        potential_move.emplace(Move(get_origin_and_taken_card.value().first,get_origin_and_taken_card.value().second));

                    break;
                }
            case sf::Event::MouseMoved:
				{
					if(potential_move.has_value())
					{
						potential_move.value().get_card().setPosition(event.mouseMove.x-(Card::actual_single_card_size.x/2),event.mouseMove.y-(Card::actual_single_card_size.y/2));
						break;
					}
				}
            case sf::Event::MouseButtonReleased:
                {

                    if(potential_move)
                    {
                        potential_move.value().set_destination([&]()-> std::shared_ptr<Deck> //ustalamy wskaźnik do decku na miejsce gdzie jest kursor
                        {
                            sf::Vector2f point (event.mouseButton.x,event.mouseButton.y);

                            for(std::shared_ptr<Deck> deck: my_board.get_decks_arrays().first) //pola bankowe sprawdzamy
                            {
                                if(deck->get_rect().contains(point)) return deck;
                            }

                            for(std::shared_ptr<Deck> deck: my_board.get_decks_arrays().second) //pola zew sprawdzamy
                            {
                                if(deck->get_rect().contains(point)) return deck;
                            }

                            if(whose_turn->get_deck_pointer()->get_rect().contains(point)) return whose_turn->get_deck_pointer();
                            if(whose_turn->get_trash_pointer()->get_rect().contains(point)) return whose_turn->get_trash_pointer(); 
                            if(get_opponents_pointer()->get_deck_pointer()->get_rect().contains(point)) return get_opponents_pointer()->get_deck_pointer();
                            if(get_opponents_pointer()->get_trash_pointer()->get_rect().contains(point)) return get_opponents_pointer()->get_trash_pointer(); 

                            //jeżeli gdziekolwiek indziej klikneliśmy
                            return nullptr;
                        }());
                        

                        players_move(potential_move.value());                                    
                        potential_move.reset();
                        
                    }
                    break;
                }
                
            }




    }


}