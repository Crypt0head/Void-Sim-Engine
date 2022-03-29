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
    bool bActive;


public:
    VEntity();
    VEntity(int x, int y, char g = 'o', bool a = true);
    virtual void Tick();
    virtual const std::pair<const int, const int> GetPosition();
    virtual const bool IsDead() {return bDead;}
    virtual ~VEntity();

};