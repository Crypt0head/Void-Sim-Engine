//
// This class should provide and control simmulation
//

#include <iostream>
#include <chrono>
#include <vector>
#include <thread>
#include <mutex>
#include <cstdlib>
#include <ctime>
#include <iomanip>

#include "VEntity.h"

class VWorld
{
protected:
    // TODO: VEntityManager needed
    std::vector<VEntity> EntMgr;

    // Sim's field params hight and width
    std::pair<int,int> Field;

    bool* bIsSimContinue;

    unsigned long long GenCounter;

public:
    VWorld();
    VWorld(std::string cfg_File);
    void Start(bool* bSimCondition, bool &bThreadTaskCompleted);
    void Tick();
    void Stop();
    void Init();
    void Update();
    int Search(int, int);
    int Search_d(int, int);
    int CountNighbors(int,int, bool = false);
    std::pair<int, std::pair<int, int>> CountNighbors(std::pair<int, std::pair<int, int>>);
    const std::pair<int,int> GetField();
    std::vector<VEntity>& GetEntMgr();
    virtual ~VWorld();

};