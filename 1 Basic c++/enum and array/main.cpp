#include <cassert>
#include <iostream>
#include <vector>

namespace animal
{   
    enum StudentNames
{
    chicken, // 0
    dog, // 1
    cat, // 2
    elephant, // 3
    duck, // 4
    snake,// 5
    max_animal
};

}


int main()
{
    std::vector<int> legOfAnimal { 2, 4, 4, 4, 2, 0 };
    // Ensure the number of test scores is the same as the number of students
    assert(std::size(legOfAnimal) == animal::max_animal);
    std::cout<<"elephent has "<<legOfAnimal[animal::elephant]<<" legs";
    return 0;
}