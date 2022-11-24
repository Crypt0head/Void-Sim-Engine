#include "../VSimMod.h"

class VSM_LifeGame: public VSimMod
{
public:
    unsigned long long GenCounter = 0;

    unsigned int Seed;

public:
    VSM_LifeGame(unsigned int = 10, unsigned int = 10, unsigned int = 50);
    virtual void Init() override;
    virtual void Start(bool*, bool&) override;
    virtual void Stop() override;
    virtual void Tick() override;
    virtual void Update() override;
    int Search_d(int x, int y);
    int Search(int x, int y);
    int CountNighbors(int x,int y, bool bSelf = false);
    std::pair<int, std::pair<int, int>> CountNighbors(std::pair<int, std::pair<int, int>> p);
    ~VSM_LifeGame();
};