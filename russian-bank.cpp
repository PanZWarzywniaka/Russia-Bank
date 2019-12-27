#include<iostream>
#include"game.hpp"
#include <utility>


int main()
{
    Card::load_texuture(); //ładowanie arkusza, dla wszystkich obiektów
    Game gra;

    //bufory do move
    bool is_card_taken = false;
    std::optional<Card> taken_card=std::nullopt;
    std::stack<Card>* wherefrom_card_is_taken=nullptr; //stos z którego bierzemy // foooking british english old use
    std::stack<Card>* whereto_card_is_taken=nullptr;

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
                    
                    if(true)//sprawdz czy kliknąłeś karte i //sprawdzenie czy nie wzieliśmy karty od przeciwnika, ani ze strefy środkowej
                    {
                        //weź karte
                        //bufory
                        is_card_taken=true;
                        //wherefrom_card_is_taken ='wkaźnik do stosu na którym jest myszka'
                        
                        //taken_card=std::move('stos na którym jest myszka')
                        //trzeba sprawdzić czy karta na pewno została zabrana bo nie mam pewności
                        //zabieramy karte ztąd// 'stos na którym jest myszka'.pop()
                    }

                    break;
                }
            case sf::Event::MouseButtonReleased:
                {
                    if(is_card_taken)
                    {
                        //weź karte
                        //whereto_card_is_taken='wkaźnik do stosu na którym jest myszka'
                        //konstruktor move
                        Move ruch(wherefrom_card_is_taken, whereto_card_is_taken, std::move(taken_card.value()));
                        gra.players_move(gra.get_whose_turn(),ruch);
                    }
                    break;
                }
                
            }




        }


        //okno
        gra.okno.clear(sf::Color::Green);
        //gra.okno.draw();
        gra.okno.display();
        

    }

    return 0;
}