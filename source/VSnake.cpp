#include "../includes/VSnake.h"

VSnake::VSnake(int x, int y,Sides dir = Sides::N, char g = 'o'): VEntity(x,y,g), Dirrection(dir){
    Body.push_back(VEntity(x,y,'o'));
    Head = &Body.front();
    Size=1;
}

void VSnake::Update(){
    for(auto part = ++Body.begin();part!=Body.end();++part)
    {
        auto prev_pos = std::prev(part)->GetPosition();
        part->SetPosition(prev_pos.first, prev_pos.second);
    }

    Move(1);
}

void VSnake::Grow()
{
    auto head_pos = Head->GetPosition();
    Body.push_front(VEntity(head_pos.first,head_pos.second,'o'));
}

void VSnake::Move(size_t steps_num = 1){
    switch(Dirrection){
        case Sides::N:
            Head->SetPosition(GetPosition().first, GetPosition().second+1);
        break;
        case Sides::E:
            Head->SetPosition(GetPosition().first+1, GetPosition().second);
        break;
        case Sides::S:
            Head->SetPosition(GetPosition().first, GetPosition().second-1);
        break;
        case Sides::W:
            Head->SetPosition(GetPosition().first-1, GetPosition().second);
        break;
    }
}

VSnake::~VSnake(){

};



