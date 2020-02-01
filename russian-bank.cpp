#include<iostream>
#include"game.hpp"
#include <utility>


int main()
{
    Card::load_texuture(); //ładowanie arkusza, dla wszystkich obiektów
    Game gra;

    //bufory do move
    std::optional<Card> taken_card=std::nullopt;
    std::shared_ptr<Deck> wherefrom_card_is_taken=nullptr; //stos z którego bierzemy // foooking british english old use
    std::shared_ptr<Deck> whereto_card_is_taken=nullptr; //pointer to const Deck

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
        gra.okno.clear(sf::Color::Green);

        gra.okno.draw(gra);
        if(taken_card)
            { 
                const Card& card = taken_card.value();
                gra.okno.draw(card);
            }

        gra.okno.display();
    }

    return 0;
}