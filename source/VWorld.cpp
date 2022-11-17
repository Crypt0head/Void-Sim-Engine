#include "../includes/VWorld.h"
#include "../includes/VEntity.h"
#include "../includes/VSimMod.h"

VWorld::VWorld(VSimMod* simMod)
{
    CurrentSimMod = simMod;
}

VWorld::VWorld(std::string cfg_File)
{
    // TODO: Implement configs loading from given file with checks
}

void VWorld::SetSimMod(VSimMod* sim)
{
    if(CurrentSimMod==nullptr)
    {
        CurrentSimMod = sim;
    }
}

VSimMod* VWorld::GetSimMod()
{
    return CurrentSimMod;
}

void VWorld::Run(bool* bSimCondition, bool &bThreadTaskCompleted)
{
    CurrentSimMod->Start(bSimCondition, bThreadTaskCompleted);
}

void VWorld::Break()
{
    //TODO: Break sumulation
}

VWorld::~VWorld()
{
    // Default distructor
    if(CurrentSimMod!=nullptr)
    {
        delete CurrentSimMod;
    }
}