#include <iostream>

namespace Devil
{
    enum MonsterType 
    {
        orc,
        goblin, 
        troll, 
        ogre, 
        skeleton,
    };
}

int main (){

    Devil::MonsterType round1 {Devil::troll};
    std::cout<<"monster is "<<round1;
    return 0;
}