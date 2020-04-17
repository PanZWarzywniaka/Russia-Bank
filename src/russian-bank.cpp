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
    std::cout<<"Starting event loop.\n";

    while(gra.is_running())
    {
        gra.event_handling();
        gra.clear_and_draw_all(); //rysuje okno d
        std::this_thread::yield();

    }

    std::cout<<"Main quits.\n";
    return 0;
}