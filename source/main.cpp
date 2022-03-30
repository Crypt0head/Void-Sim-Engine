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
#include <boost/json.hpp>
#include <boost/program_options.hpp>
// #include <boost/...>

#include "../header/VWorld.h"

// Simple CL output function
// TODO: Implament simple SDL rendering engine
void Print(VWorld &World)
{
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
    bool bThreadTaskCompleted = false;
    char Command = 0;

    // Run World simulation in a separate thread
    std::thread WorldThread([&World, &bSimulate, &bThreadTaskCompleted](){World.Start(bSimulate, bThreadTaskCompleted);});

    while(*bSimulate)
    {
        if(bThreadTaskCompleted)
        {
            Print(World);
            bThreadTaskCompleted = false;
        }
    }

    // Wait untile sim over
    WorldThread.join();

    delete bSimulate;

    return 0;
}