#include "../includes/SimMods/VSM_SnakeGame.h"
#include "../includes/VSnake.h"


VSM_SnakeGame::VSM_SnakeGame(unsigned int w, unsigned int h) : VSimMod(w,h){
    Snake = new VSnake(5,5,Sides::N,'o');
    EntMgr.push_back(*Snake->Head); //TODO: Find a way to send new snake parts to EntMgr
};

void VSM_SnakeGame::Start(bool* bSimCondition, bool &bThreadTaskCompleted)
{
    Init();
    this->VSimMod::Start(bSimCondition,bThreadTaskCompleted);
}

void VSM_SnakeGame::Tick(){}

void VSM_SnakeGame::Stop()
{
    std::cout<< "\n" <<"SIMULATION IS OVER" << "\n";
}

void VSM_SnakeGame::Init()
{
    this->VSimMod::Init();

}

// Updating Entities properties
void VSM_SnakeGame::Update()
{
    if(!EntMgr.empty())
    {
        Snake->Update();
    }
}

VSM_SnakeGame::~VSM_SnakeGame(){
    delete Snake;
    delete Food;
};