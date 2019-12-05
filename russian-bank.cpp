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
                
            
                default:
                break;
            }




        }
        

    }

    return 0;
}