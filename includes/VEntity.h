// Base class for Entities on the Field
#pragma once
#include <iostream>

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
    virtual void Update();
    virtual const std::pair<const int, const int> GetPosition();
    virtual void SetPosition(int x, int y);
    virtual const bool IsDead() {return bDead;}
    virtual bool operator==(const VEntity&);
    virtual ~VEntity();
};