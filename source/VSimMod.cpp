#include "../includes/VEntity.h"
#include "../includes/VSimMod.h"

VSimMod::VSimMod(){};

void VSimMod::Start(bool *bSimCondition, bool &bThreadTaskCompleted){}

void VSimMod::Tick(){}

void VSimMod::Stop()
{
    std::cout<< "\n" <<"SIMULATION IS OVER" << "\n";
}

void VSimMod::Init(){
    std::cout<< "\n" <<"SIMULATION: "<<Name<<" initialization."<< "\n";
}

void VSimMod::Update(){}

std::string VSimMod::GetName() const{
    return Name;
}

std::string VSimMod::GetDescription() const
{
    return Description;
}

std::vector<VEntity>& VSimMod::GetEntMgr()
{
    return EntMgr;
}

std::pair<int, int> VSimMod::GetField()
{
    return Field;
}

void VSimMod::Break()
{
    //*bIsSimContinue = false; not valid way to break sims
}

VSimMod::~VSimMod(){}