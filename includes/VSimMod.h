//
//    This class provides simulations logic
//
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>

class VEntity;

class VSimMod
{
public:
    bool bThreadTaskCompleted;
    bool *bIsSimContinue;

protected:
    std::string Name;
    std::string Description;
    std::vector<VEntity> EntMgr;
    std::pair<int,int> Field;

public:
    VSimMod();
    virtual void Init();
    virtual void Start(bool*, bool&);
    virtual void Stop();
    virtual void Tick();
    virtual void Update();
    virtual std::string GetName() const;
    virtual std::string GetDescription() const;
    virtual std::vector<VEntity>& GetEntMgr();
    virtual std::pair<int, int> GetField();
    virtual void Break();
    virtual ~VSimMod();
};