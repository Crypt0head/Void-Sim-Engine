#include "../includes/VEntity.h"
#include "../includes/VSimMod.h"

VSimMod::VSimMod(int x, int y): Field(std::make_pair(x,y)){};

void VSimMod::Start(bool *bSimCondition, bool &bThreadTaskCompleted){
    bThreadTaskCompleted = true;
    bIsSimContinue = bSimCondition;

    while(*bIsSimContinue)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        Update();
        bThreadTaskCompleted = true;
    }

    Stop();
}

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