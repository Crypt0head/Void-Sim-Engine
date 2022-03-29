#include "../header/VEntity.h"

VEntity::VEntity()
{
    NeighborsCount = 0;
    bDead = false;
}

VEntity::VEntity(int x, int y, char g, bool a)
{
    Position = std::pair<int,int>(x,y);
    Gen = g;
    bActive = a;
    NeighborsCount = 0;
    bDead = false;
}

void VEntity::Tick()
{
    if(NeighborsCount < 2 || NeighborsCount > 3)
    {
        bDead = true;
        bActive = false;
    }   
}

const std::pair<const int, const int> VEntity::GetPosition()
{
    return Position;
}

VEntity::~VEntity()
{

}