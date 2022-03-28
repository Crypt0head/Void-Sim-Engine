// TODO:
// 1. Implament cfg reading from json file 
// 2. Create a simple classes World, (BASE)Entity, Person, Plant, Animal.
// 3. Create a simple API to get basic info from the World sim class.
// ...

#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
// #include <boost/json>
#include <boost/program_options.hpp>
// #include <boost/...>

#include "../header/VWorld.h"

// Simple CL output function
// TODO: Implament simple SDL rendering engine
void Print(VWorld &World)
{
    //std::cout << "\n\n\n" << std::setfill('*') << std::setw(61) << "\n\n\n";
    system("clear");

    std::vector<std::string> ScrOutput;

    bool bEntity = false;
    for(int i = 0; i<World.GetField().first; ++i)
    {
        for(int j = 0; j<World.GetField().second; ++j)
        {
            bEntity = false;
            char Gen = ' ';
            for(VEntity& Entity : World.GetEntMgr())
            {
                if(Entity.GetPosition().first == i && Entity.GetPosition().second == j)
                {
                    Gen = Entity.Gen;
                }
            }   

            std::cout << Gen <<" ";
        }
        std::cout << std::endl;
    }
}


int main(int argc, char* argv[])
{
    VWorld World;
    bool* bSimulate = new bool(true);
    char Command = 0;

    // Run World simulation in a separate thread
    std::thread WorldThread([&World, &bSimulate](){World.Start(bSimulate);});

    while(*bSimulate)
    {
        Print(World);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    // Wait untile sim over
    WorldThread.join();

    delete bSimulate;

    return 0;
}