#include "../VSimMod.h"

class VSnake;

class VSM_SnakeGame : public VSimMod{
public:
    VSnake* Snake;
    VEntity* Food;
public:
    VSM_SnakeGame(unsigned int = 10, unsigned int = 10);
    virtual void Init() override;
    virtual void Start(bool*, bool&) override;
    virtual void Stop() override;
    virtual void Tick() override;
    virtual void Update() override;
    ~VSM_SnakeGame();
};