#include<iostream>
#include"game.hpp"
#include <utility>


int main()
{
    Card::load_texuture(); //ładowanie arkusza, dla wszystkich obiektów
    Game gra;

    //bufory do move
    std::optional<Card> taken_card=std::nullopt;
    Deck* wherefrom_card_is_taken=nullptr; //stos z którego bierzemy // foooking british english old use
    Deck* whereto_card_is_taken=nullptr;

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
                    
                    auto deck_checker = [&]() -> bool 
                    {
                        sf::Vector2f point (event.mouseButton.x,event.mouseButton.y);

                        for(const Deck deck: gra.get_board().get_decks_arrays().first) //pola bankowe sprawdzamy, nigdy nie można wziąć karty z banku
                        {
                            if(deck.get_rect().contains(point)) return false;
                        }

                        for(const Deck deck: gra.get_board().get_decks_arrays().second) //pola zew sprawdzamy, zawsze można wziąć karty
                        {
                            if(deck.get_rect().contains(point)) return true;
                        }

                        if(gra.get_players_pointer()->get_deck_pointer()->get_rect().contains(point)) return true; //pozwalamy na dobranie karty ze swojej tali
                        if(gra.get_players_pointer()->get_trash_pointer()->get_rect().contains(point)) return true; //pozwalamy na dobranie karty ze swojego kosza
                        if(gra.get_opponents_pointer()->get_deck_pointer()->get_rect().contains(point)) return false; //nie pozwalamy na dobranie karty z tali przeciwnika
                        if(gra.get_opponents_pointer()->get_trash_pointer()->get_rect().contains(point)) return false; //nie pozwalamy na dobranie karty z kosza przeciwnika

                        //jeżeli gdzie kolwiek indziej klikneliśmy
                        return false;
                    }();
                    

                    if(deck_checker)//sprawdz czy kliknąłeś karte i //sprawdzenie czy nie wzieliśmy karty od przeciwnika, ani ze strefy środkowej
                    {
                        //bufory
                        //weź karte taken_card=true;
                        //wherefrom_card_is_taken ='wkaźnik do stosu na którym jest myszka'
                        
                        //taken_card=std::move('stos na którym jest myszka')
                        //trzeba sprawdzić czy karta na pewno została zabrana bo nie mam pewności
                        //zabieramy karte ztąd// 'stos na którym jest myszka'.pop()
                    }
                    
                    break;
                }
            case sf::Event::MouseButtonReleased:
                {
                    if(taken_card.has_value())
                    {
                        //weź karte
                        //whereto_card_is_taken='wkaźnik do stosu na którym jest myszka'
                        //konstruktor move
                        Move ruch(wherefrom_card_is_taken, whereto_card_is_taken, std::move(taken_card.value()));
                        gra.players_move(gra.get_players_pointer(),ruch);
                    }
                    break;
                }
                
            }




        }


        //okno
        gra.okno.clear(sf::Color::Green);
        gra.okno.draw(gra);
        gra.okno.display();
        

    }

    return 0;
}