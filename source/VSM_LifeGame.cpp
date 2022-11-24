#include "../includes/SimMods/VSM_LifeGame.h"
#include "../includes/VEntity.h"

VSM_LifeGame::VSM_LifeGame(unsigned int w, unsigned int h, unsigned int seed) : VSimMod(w,h), Seed(seed){};

void VSM_LifeGame::Start(bool* bSimCondition, bool &bThreadTaskCompleted)
{
    Init();
    this->VSimMod::Start(bSimCondition,bThreadTaskCompleted);
}

void VSM_LifeGame::Tick(){}

void VSM_LifeGame::Stop()
{
    std::cout<< "\n" <<"SIMULATION IS OVER" << "\n";
    std::cout<<"TOTAL GENERATIONS: " << GenCounter << "\n";
}

//  Init() func generate from 0 to 100 Entities with random unique coords
void VSM_LifeGame::Init()
{
    this->VSimMod::Init();
    std::srand(std::time(nullptr));

    int Turns = rand() % Seed;

    for(int i = 0; i< Turns; ++i)
    {
        VEntity TmpEntity(rand() % Field.first, rand() % Field.second);
        bool bUnique = true;


        for(VEntity Entity : EntMgr)
        {
            if(Entity.GetPosition().first == TmpEntity.GetPosition().first && Entity.GetPosition().second == TmpEntity.GetPosition().second)
            {
                --i;
                bUnique = false;
                break;
            }
        }

        if(bUnique)
        {
            EntMgr.push_back(TmpEntity);
        }
    }
}

// Updating Entities properties
void VSM_LifeGame::Update()
{
    if(!EntMgr.empty())
    {
        // Born new Generation
        char Gen = 97 + rand() % 30;
        int size = EntMgr.size(); // remove after fix
        for(std::vector<VEntity>::iterator it = EntMgr.begin();it != EntMgr.end();++it)
        {
            if(!it->IsDead() && !it->bActive)
            {it->bActive = true;}
        }

        int count = 0;

        for(auto it_1 = EntMgr.begin();it_1!=EntMgr.end();++it_1)
        {
            VEntity &Entity = *it_1;
            int size = EntMgr.size(); // remove after fix
            count++;
            Entity.NeighborsCount = CountNighbors(Entity.GetPosition().first, Entity.GetPosition().second, true);

            Entity.Tick();

            // Checking all cells around current Entity
            std::pair<int, std::pair<int, int>> NeghborsCount[8]; // TODO: maybe will be better to use struct?
            NeghborsCount[0] = CountNighbors(std::pair<int, std::pair<int, int>>(0,std::pair<int, int>(Entity.GetPosition().first-1, Entity.GetPosition().second-1)));
            NeghborsCount[1] = CountNighbors(std::pair<int, std::pair<int, int>>(0,std::pair<int, int>(Entity.GetPosition().first, Entity.GetPosition().second-1)));
            NeghborsCount[2] = CountNighbors(std::pair<int, std::pair<int, int>>(0,std::pair<int, int>(Entity.GetPosition().first+1, Entity.GetPosition().second-1)));
            NeghborsCount[3] = CountNighbors(std::pair<int, std::pair<int, int>>(0,std::pair<int, int>(Entity.GetPosition().first-1, Entity.GetPosition().second)));
            NeghborsCount[4] = CountNighbors(std::pair<int, std::pair<int, int>>(0,std::pair<int, int>(Entity.GetPosition().first+1, Entity.GetPosition().second)));
            NeghborsCount[5] = CountNighbors(std::pair<int, std::pair<int, int>>(0,std::pair<int, int>(Entity.GetPosition().first-1, Entity.GetPosition().second+1)));
            NeghborsCount[6] = CountNighbors(std::pair<int, std::pair<int, int>>(0,std::pair<int, int>(Entity.GetPosition().first, Entity.GetPosition().second+1)));
            NeghborsCount[7] = CountNighbors(std::pair<int, std::pair<int, int>>(0,std::pair<int, int>(Entity.GetPosition().first+1, Entity.GetPosition().second+1)));

            for(int i=0;i<8;++i)
            {
                if(NeghborsCount[i].first == 3)
                    {

                        int size = EntMgr.size(); // remove after fix
                        EntMgr.push_back(VEntity(NeghborsCount[i].second.first, NeghborsCount[i].second.second, Gen, false));
                        GenCounter++;
                    }
            }
        }

        auto iter = EntMgr.begin();
        while(iter!=EntMgr.end())
        {
            if(iter->IsDead())
            {
                if(iter != EntMgr.end()-1)
                {
                    EntMgr.erase(iter);
                    continue;
                }
                else
                {
                    EntMgr.pop_back();
                    break;
                }
            }
            ++iter;
        }
    }
    else
    {
        *bIsSimContinue = false;
    }
}

// Returns true if any Entities matches with coords
int VSM_LifeGame::Search(int x, int y)
{
    bool bMatch = false;

    for(VEntity Entity : EntMgr)
    {
        if(Entity.GetPosition().first == x && Entity.GetPosition().second == y)
        {
            if(Entity.bActive)
            {
                bMatch = true;
            }
            else
            {
                return -1;
            }
        }
    }

    return (int)bMatch;
}

int VSM_LifeGame::Search_d(int x, int y) // Find another solution
{
    bool bMatch = false;

    for(VEntity Entity : EntMgr)
    {
        if(Entity.GetPosition().first == x && Entity.GetPosition().second == y)
        {
            if(Entity.bActive)
            {
                bMatch = true;
            }
        }
    }

    return (int)bMatch;
}

int VSM_LifeGame::CountNighbors(int x,int y, bool bSelf)
{
    int NeighborsCounter = 0;

    if(bSelf)
    {
        NeighborsCounter = Search_d((x-1)%Field.first, (y-1)%Field.second) +
                        Search_d(x, (y-1)%Field.second) + Search_d((x+1)%Field.first, (y-1)%Field.second) +
                        Search_d((x-1)%Field.first, y) + Search_d((x+1)%Field.first, y) +
                        Search_d((x-1)%Field.first, (y+1)%Field.second) 
                        + Search_d(x, (y+1)%Field.second) + 
                        Search_d((x+1)%Field.first, (y+1)%Field.second);
    }
    else if(!Search(x,y))
    {
        NeighborsCounter = Search((x-1)%Field.first, (y-1)%Field.second) +
                        Search(x, (y-1)%Field.second) + Search((x+1)%Field.first, (y-1)%Field.second) +
                        Search((x-1)%Field.first, y) + Search((x+1)%Field.first, y) +
                        Search((x-1)%Field.first, (y+1)%Field.second) 
                        + Search(x, (y+1)%Field.second) + 
                        Search((x+1)%Field.first, (y+1)%Field.second);
    }

    return NeighborsCounter;
}

std::pair<int, std::pair<int, int>> VSM_LifeGame::CountNighbors(std::pair<int, std::pair<int, int>> p)
{
    std::pair<int, std::pair<int, int>> result = p;
    result.first = CountNighbors(p.second.first, p.second.second);

    return result;
}

VSM_LifeGame::~VSM_LifeGame(){};