//
// This class should provide and control simmulation
//
#pragma once
#include <iostream>
// #include <chrono>
#include <vector>
// #include <cstdlib>
// #include <ctime>
// #include <iomanip>

class VEntity;

class VSimMod;

class VWorld
{
protected:
    // SimMod provides simulation program 
    VSimMod* CurrentSimMod;


public:
    VWorld(VSimMod* = nullptr);
    VWorld(std::string cfg_File);
    void SetSimMod(VSimMod* sim);
    VSimMod* GetSimMod();
    void Run(bool*, bool&);
    void Break();
    virtual ~VWorld();
};