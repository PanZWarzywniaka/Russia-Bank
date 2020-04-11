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
    while(gra.is_running())
    {
        sf::Event event;
        gra.event_handling();
        gra.clear_and_draw_all(taken_card); //rysuje okno z ewentualnym taken_card
        std::this_thread::yield();

    }

    std::cout<<"Main quits.\n";
    return 0;
}