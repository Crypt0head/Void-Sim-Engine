#include "../includes/VEntity.h"

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
    if((NeighborsCount < 2 || NeighborsCount > 3) && !this->bDead)
    {
        bDead = true;
    }   
}

const std::pair<const int, const int> VEntity::GetPosition()
{
    return Position;
}

bool VEntity::operator==(const VEntity& ent)
{
    if((this->Position == ent.Position) && (this->Gen == ent.Gen) && (this->bActive == ent.bActive))
    {
        return true;
    }

    return false;
}

VEntity::~VEntity()
{

}