#include <iostream>
#include "game.hpp"
#include <utility>
#include <thread>
#include <mutex>


int main()
{
    std::cout<<"Hello from main. Loading textures...\n";
    Card::load_texuture(); //ładowanie arkusza, dla wszystkich obiektów
    std::cout<<"Done.\n";
    std::cout<<"Constructing the Game object...\n";
    Game gra;
    std::cout<<"Done.\n";
    server_client client; //test bindingu, siema elo, to nic nie robi w kodzie, ale se tym testuję binding
    //bufory do move
    std::optional<Card> taken_card=std::nullopt;
    std::shared_ptr<Deck> wherefrom_card_is_taken=nullptr; //stos z którego bierzemy // foooking british english old use
    std::shared_ptr<Deck> whereto_card_is_taken=nullptr; //pointer to const Deck

    std::cout<<"Starting event loop.\n";
    while(gra.okno.isOpen())
    {
        sf::Event event;
        while (gra.okno.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                {
                    gra.okno.close();
                    break;
                }
            case sf::Event::Resized:
                {   
                    
                    static std::chrono::system_clock::time_point lastresize;
                    static std::mutex lr_mut;

                    lr_mut.lock();
                    lastresize = std::chrono::system_clock::now();
                    lr_mut.unlock();

                    sf::Event::SizeEvent size = event.size;
                    unsigned int edge = std::min(size.height,size.width);
                    while(edge%32!=0) edge--;

                    auto defer_resize = [&gra](std::chrono::system_clock::time_point& lastresize, std::mutex& lr_mut, unsigned int edge)
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
                            std::lock_guard my_lock(gra.game_mutex); //prevent raid with drawing
                            gra.okno.setSize({edge,edge});
                            sf::View new_view;
                            new_view.setSize(edge,edge);
                            new_view.setCenter(edge/2,edge/2);
                            gra.okno.setView(new_view);
                                //GRA
                            gra.set_scale(static_cast<double>(edge)/1000); //ustawienie odpowiedniej skali
                            gra.window_scaling();
                            
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
                    
                    wherefrom_card_is_taken = [&]() -> std::shared_ptr<Deck> /*tu odbywa się walidacja skąd możemy zabrać karte*/ 
                    {
                        auto assign = [&](std::shared_ptr<Deck>& target)
                        {
                            Card the_victim = target->top();
                            target->pop();
                            taken_card.emplace(the_victim);
                            taken_card.value().setPosition(event.mouseButton.x-(Card::actual_single_card_size.x/2),event.mouseButton.y-(Card::actual_single_card_size.y/2));
                        };

                        sf::Vector2f point (event.mouseButton.x,event.mouseButton.y);

                        for(const std::shared_ptr<Deck> deck: gra.get_board().get_decks_arrays().first) //pola bankowe sprawdzamy, nigdy nie można wziąć karty z banku
                        {   
                            if(!deck->empty())
                                if(deck->get_rect().contains(point)) 
                                    return nullptr;
                        }

                        for(std::shared_ptr<Deck> deck: gra.get_board().get_decks_arrays().second) //pola zew sprawdzamy, zawsze można wziąć karty
                        {
                            if(!deck->empty())
                                if(deck->get_rect().contains(point))
                                {
                                    std::shared_ptr<Deck> wskaznik = deck;//tu jest bug ale niew wiem jak go naprawić wherefrome_car_is_taken nie dostaje dobrego wskaźnika
                                    assign(wskaznik);
                                    return wskaznik;
                                }
                        }
                        if(!gra.get_players_pointer()->get_deck_pointer()->empty())
                        {
                            if(gra.get_players_pointer()->get_deck_pointer()->get_rect().contains(point))
                            {
                                std::shared_ptr<Deck> wskaznik = gra.get_players_pointer()->get_deck_pointer();
                                assign(wskaznik);
                                return wskaznik;
                            } 
                           
                        }
            
                        if(!gra.get_players_pointer()->get_trash_pointer()->empty())
                        {
                            if(gra.get_players_pointer()->get_trash_pointer()->get_rect().contains(point)) 
                            {
                                std::shared_ptr<Deck> wskaznik = gra.get_players_pointer()->get_trash_pointer(); //pozwalamy na dobranie karty ze swojego kosza
                                assign(wskaznik);
                                return wskaznik;
                            }
                        }
                        
                        
                        //jeżeli gdzie kolwiek indziej klikneliśmy
                        return nullptr;
                    }();
                    
                    /*
                    if(wherefrom_card_is_taken)//sprawdz czy kliknąłeś karte i //sprawdzenie czy nie wzieliśmy karty od przeciwnika, ani ze strefy środkowej
                    {
                        //taken_card = std::move(wherefrom_card_is_taken->top());
                        //taken_card = wherefrom_card_is_taken->top();
                        //nie wiem czemu wywala błąd w tych linijkach

                        
                        
                        //if(wherefrom_card_is_taken->top()==taken_card.value()) throw std::runtime_error("Card obtaining Error");
                    }
                    */
                    break;
                }
            case sf::Event::MouseMoved:
				{
					if(taken_card && wherefrom_card_is_taken)
					{
						taken_card.value().setPosition(event.mouseMove.x-(Card::actual_single_card_size.x/2),event.mouseMove.y-(Card::actual_single_card_size.y/2));
						break;
					}
				}
            case sf::Event::MouseButtonReleased:
                {

                    if(taken_card && wherefrom_card_is_taken)
                    {
                        //ustalamy wskaźnik do decku na miejsce gdzie jest kursor
                        whereto_card_is_taken = [&]() -> std::shared_ptr<Deck> /*tu NIE odbywa się walidacja dokąd możemy dać karte, sprawdzanie robie gra.players_move()*/
                        {
                            sf::Vector2f point (event.mouseButton.x,event.mouseButton.y);

                            for(std::shared_ptr<Deck> deck: gra.get_board().get_decks_arrays().first) //pola bankowe sprawdzamy
                            {
                                if(deck->get_rect().contains(point)) return deck;
                            }

                            for(std::shared_ptr<Deck> deck: gra.get_board().get_decks_arrays().second) //pola zew sprawdzamy
                            {
                                if(deck->get_rect().contains(point)) return deck;//tu jest bug ale niew wiem jak go naprawić wherefrome_car_is_taken nie dostaje dobrego wskaźnika
                            }

                            if(gra.get_players_pointer()->get_deck_pointer()->get_rect().contains(point)) return gra.get_players_pointer()->get_deck_pointer();
                            if(gra.get_players_pointer()->get_trash_pointer()->get_rect().contains(point)) return gra.get_players_pointer()->get_trash_pointer(); 
                            if(gra.get_opponents_pointer()->get_deck_pointer()->get_rect().contains(point)) return gra.get_opponents_pointer()->get_deck_pointer();
                            if(gra.get_opponents_pointer()->get_trash_pointer()->get_rect().contains(point)) return gra.get_opponents_pointer()->get_trash_pointer(); 

                            //jeżeli gdziekolwiek indziej klikneliśmy
                            return nullptr;
                        }();

                        Move ruch(wherefrom_card_is_taken,whereto_card_is_taken,std::move(taken_card.value())); 
                        gra.players_move(ruch);                                    
                        
                        taken_card = std::nullopt;
                        wherefrom_card_is_taken = nullptr;
                        whereto_card_is_taken = nullptr;
                        
                    }
                    break;
                }
                
            }




        }


        //okno
        gra.clear_and_draw_all(taken_card); //rysuje okno z ewentualnym taken_card
        std::this_thread::yield();

    }

    std::cout<<"Main quits.\n";
    return 0;
}