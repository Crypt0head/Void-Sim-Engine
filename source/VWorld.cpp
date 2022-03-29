#include "../header/VWorld.h"

VWorld::VWorld()
{
    Field.first=60;
    Field.second=60;
    EntMgr.reserve(6);
    GenCounter = 1;
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
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        Update();
        //Tick();
    }

    Stop();
}

void VWorld::Tick()
{
    // if(EntMgr.size() != 0)
    // {
    //     for(VEntity &Entity : EntMgr)
    //     {
    //         Entity.Tick();
    //     }
    // }
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

    int Turns = rand() % 1500;

    // EntMgr.push_back(VEntity(1,2, '1')); EntMgr.push_back(VEntity(2,2,'2')); EntMgr.push_back(VEntity(3,2,'3'));
    //                                                                 EntMgr.push_back(VEntity(3,1,'4'));
    //                                 EntMgr.push_back(VEntity(2,0, '5'));

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
        std::vector<VEntity>::iterator EntityIterator = EntMgr.begin();

        for(std::vector<VEntity>::iterator it = EntMgr.begin();it != EntMgr.end();it++)
        {
            EntityIterator->bActive = true;
        }

        for(int i=0;i<Field.first;i++)
        {
            for(int j= 0;j<Field.second;j++)
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
                        int size = EntMgr.size();
                        EntMgr.push_back(VEntity(i, j, Gen, false));
                        GenCounter++;
                    }
                }
                else
                {
                    // Revision population

                    int size = EntMgr.size();
                    EntityIterator->NeighborsCount = 
                    Search((EntityIterator->GetPosition().first-1)%Field.first, 
                    (EntityIterator->GetPosition().second-1)%Field.second) +
                    Search(EntityIterator->GetPosition().first, (EntityIterator->GetPosition().second-1)%Field.second) + 
                    Search((EntityIterator->GetPosition().first+1)%Field.first, (EntityIterator->GetPosition().second-1)%Field.second) +
                    Search((EntityIterator->GetPosition().first-1)%Field.first, EntityIterator->GetPosition().second) + 
                    Search((EntityIterator->GetPosition().first+1)%Field.first, EntityIterator->GetPosition().second) +
                    Search((EntityIterator->GetPosition().first-1)%Field.first, (EntityIterator->GetPosition().second+1)%Field.second) + 
                    Search(EntityIterator->GetPosition().first, (EntityIterator->GetPosition().second+1)%Field.second) + 
                    Search((EntityIterator->GetPosition().first+1)%Field.first, (EntityIterator->GetPosition().second+1)%Field.second);

                    EntityIterator->Tick();

                    if(EntityIterator->IsDead())
                    {
                        EntMgr.erase(EntityIterator);
                    }
                    if(EntityIterator != EntMgr.end())
                    {
                        EntityIterator++;
                    }
                }
            }
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
        if(Entity.GetPosition().first == std::abs(x) && Entity.GetPosition().second == abs(y) && Entity.bActive)
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