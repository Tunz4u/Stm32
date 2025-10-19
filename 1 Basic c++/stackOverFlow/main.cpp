#include <cstddef>
#include <iostream>
#include <string>
#include <iterator>
#include <utility>
#include <algorithm>
int main()
{
    std::cout << "How many names would you like to enter? ";
    std::size_t length{};
    std::cin >> length;

    auto* array{ new std::string[length]{} }; // use array new.  Note that length does not need to be constant!

    for(size_t index=0;index<length;index++)
    {  
        std::cout<<"Enter name #"<<index+1<<": ";
        std::getline(std::cin>>std::ws,array[index]);
    }

    std::sort(array, array + length);

    std::cout<<"Here is your sorted list: \n";
    for(size_t index=0;index<length;index++)
    {
        std::cout<<"Name #"<<index+1<<": "<<array[index]<<"\n";
    }

    delete[] array; // use array delete to deallocate array

    // we don't need to set array to nullptr/0 here because it's going out of scope immediately after this anyway

    return 0;
}