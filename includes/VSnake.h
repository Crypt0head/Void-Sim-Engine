// TODO: Base class for all snake, inherited from VAnimal
#include <list>

#include "VEntity.h"

enum class Sides {N,E,S,W};

class VSnake: public VEntity{
public:
    std::list<VEntity> Body;
    VEntity* Head;
    Sides Dirrection;
    size_t Size;

public:
    VSnake() = delete;
    VSnake(int x, int y, Sides dir, char g);
    void Update() override;
    virtual void Move(size_t steps_num);
    virtual void Grow();
    virtual ~VSnake();
};