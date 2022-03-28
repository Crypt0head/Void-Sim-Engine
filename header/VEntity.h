#include <iostream>
#include <chrono>
#include <thread>


class VEntity
{
private:
    std::pair<int,int> Position;
    bool bDead;

public:
    int NeighborsCount;
    char Gen;


public:
    VEntity();
    VEntity(int x, int y, char g = 'o');
    virtual void Tick();
    virtual const std::pair<int,int> GetPosition();
    virtual const bool IsDead() {return bDead;}
    virtual ~VEntity();

};