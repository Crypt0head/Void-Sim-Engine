#include "../header/VWorld.h"

VWorld::VWorld()
{
    Field.first=50;
    Field.second=50;
    GenCounter = 0;
}

VWorld::VWorld(std::string cfg_File)
{
    // TODO: Implement configs loading from given file with checks
}

void VWorld::Start(bool* bSimCondition)
{
    Init();
    
    bIsSimContinue = bSimCondition;

    while(*bIsSimContinue)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
        Update();
        Tick();
    }

    Stop();
}

void VWorld::Tick()
{
    if(EntMgr.size() != 0)
    {
        for(VEntity &Entity : EntMgr)
        {
            Entity.Tick();
        }
    }
}

void VWorld::Stop()
{
    std::cout<< "\n" <<"SIMULATION IS OVER" << "\n";
    std::cout<<"TOTAL GENERATIONS: " << GenCounter << "\n";
}

//  Init() func generate from 0 to 100 Entities with random unique coords
void VWorld::Init()
{
    std::srand(std::time(nullptr));

    int Turns = rand() % 500;

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
void VWorld::Update()
{
    if(!EntMgr.empty())
    {

        // Born new Generation
        char Gen = 97 + rand() % 25;

        for(int i=0;i<Field.first;++i)
        {
            for(int j= 0;j<Field.second;++j)
            {
                int NeighborsCounter = 0;
                if(!Search(i, j))
                {
                    NeighborsCounter = Search((i-1)%Field.first, (j-1)%Field.second) +
                    Search(i, (j-1)%Field.second) + Search((i+1)%Field.first, (j-1)%Field.second) +
                    Search((i-1)%Field.first, j) + Search((i+1)%Field.first, j) +
                    Search((i-1)%Field.first, (j+1)%Field.second) + Search(i, (j+1)%Field.second) + 
                    Search((i+1)%Field.first, (j+1)%Field.second);

                    if(NeighborsCounter == 3)
                    {
                        EntMgr.push_back(VEntity(i, j, Gen));
                        GenCounter++;
                    }
                }
            }
        }


        // Revision population
        std::vector<VEntity>::iterator EntityIterator = EntMgr.begin();
        for(VEntity &Entity : EntMgr)
        {
            if(!Entity.IsDead())
            {
                Entity.NeighborsCount = Search((Entity.GetPosition().first-1)%Field.first, (Entity.GetPosition().second-1)%Field.second) +
                Search(Entity.GetPosition().first, (Entity.GetPosition().second-1)%Field.second) + Search((Entity.GetPosition().first+1)%Field.first, (Entity.GetPosition().second-1)%Field.second) +
                Search((Entity.GetPosition().first-1)%Field.first, Entity.GetPosition().second) + Search((Entity.GetPosition().first+1)%Field.first, Entity.GetPosition().second) +
                Search((Entity.GetPosition().first-1)%Field.first, (Entity.GetPosition().second+1)%Field.second) + Search(Entity.GetPosition().first, (Entity.GetPosition().second+1)%Field.second) + 
                Search((Entity.GetPosition().first+1)%Field.first, (Entity.GetPosition().second+1)%Field.second);
            }
            else
            {
                EntMgr.erase(EntityIterator);
                continue;
            }
            ++EntityIterator;        
            
        }
    }
    else
    {
        *bIsSimContinue = false;
    }
}

// Returns true if any Entities matches with coords
int VWorld::Search(int x, int y)
{
    int bMatch = false;

    for(VEntity Entity : EntMgr)
    {
        if(Entity.GetPosition().first == abs(x) && Entity.GetPosition().second == abs(y))
        {
            bMatch = true;
        }
    }

    return (int)bMatch;
}

const std::pair<int,int> VWorld::GetField()
{
    return Field;
}

std::vector<VEntity>& VWorld::GetEntMgr()
{
    return EntMgr;
}

VWorld::~VWorld()
{
    // Default distructor
}