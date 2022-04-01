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

namespace opt = boost::program_options;

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


int main(int argc, char *argv[])
{
    VWorld* World = nullptr;

    opt::options_description description("All options");

    description.add_options()
    ("field", opt::value<int>(), "Field settings NxN")
    ("seed,s", opt::value<int>(), "Amount of Entity on start of simulation")
    ("cfg-file,f", opt::value<std::string>(), "Path to config file")
    ("help,h", "Help messsage");

    opt::variables_map vm;

    opt::store(opt::parse_command_line(argc, argv, description), vm);

    opt::notify(vm);

    if(vm.count("help"))
    {
        std::cout << description << "\n";
        return 1;
    }

    if(vm.count("cfg-file"))
    {
        // TODO: Implement input from config file
    }
    else if(vm.count("field"))
    {
        World = new VWorld(vm["field"].as<int>(), vm["field"].as<int>(), (vm.count("seed")) ? vm["seed"].as<int>() : vm["field"].as<int>()/2);    
        // TODO: Check if seed arg valid
    }
    else
    {
        World = new VWorld(10,10,50);
    }

    //VWorld World;

    bool* bSimulate = new bool(true);
    bool bThreadTaskCompleted = false;
    char Command = 0;

    // Run World simulation in a separate thread
    std::thread WorldThread([&World, &bSimulate, &bThreadTaskCompleted](){World->Start(bSimulate, bThreadTaskCompleted);});

    while(*bSimulate)
    {
        if(bThreadTaskCompleted)
        {
            Print(*World);
            bThreadTaskCompleted = false;
        }
    }

    // Wait untile sim over
    WorldThread.join();

    delete bSimulate;
    
    if(World != nullptr)
    {
       delete World;
    }

    return 0;
}