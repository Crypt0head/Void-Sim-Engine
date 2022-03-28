#include "../header/VEntity.h"

VEntity::VEntity()
{
    NeighborsCount = 0;
    bDead = false;
}

VEntity::VEntity(int x, int y, char g)
{
    Position = std::pair<int,int>(x,y);
    Gen = g;
    NeighborsCount = 0;
    bDead = false;
}

void VEntity::Tick()
{
    if(NeighborsCount < 2 || NeighborsCount > 3)
    {
        bDead = true;
    }   
}

const std::pair<int,int> VEntity::GetPosition()
{
    return Position;
}

VEntity::~VEntity()
{

}