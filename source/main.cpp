// TODO:
// 1. Implament cfg reading from json file 
// 2. Create a simple classes World, (BASE)Entity, Person, Plant, Animal.
// 3. Create a simple API to get basic info from the World sim class.
// ...

#include "iostream"
#include "thread"
#include "chrono"
#include "ctime"
// #include "boost/json"
#include "boost/program_options.hpp"
// #include "boost/..."


int main(int argc, char* argv[])
{
    auto cur_time = std::chrono::high_resolution_clock::now();
    time_t time = std::chrono::system_clock::to_time_t(cur_time);
    std::cout<<std::ctime(&time)<<std::endl;

    return 0;
}