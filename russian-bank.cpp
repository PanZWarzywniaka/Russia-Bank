#include<iostream>
#include"game.hpp"



int main()
{
    Game gra;
    bool is_card_taken = false;

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
                    if()//sprawdz czy kliknąłeś karte
                    {
                        //weź karte
                        is_card_taken=true;
                    }
                    break;
                }
            case sf::Event::MouseButtonReleased:
                {
                    if (is_card_taken)
                    {
                        //konstruktor move
                    }
                    break;
                }
                
            }




        }

        gra.players_turn(gra.get_whose_turn(),gra.get_board());
        gra.okno.clear(sf::Color::Green);
        //gra.okno.draw();
        gra.okno.display();
        

    }

    return 0;
}