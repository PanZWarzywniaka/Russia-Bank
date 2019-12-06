#include<iostream>
#include"game.hpp"

int main()
{
    Game gra;

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