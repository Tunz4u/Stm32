#include <iostream>
#include <ranges> // C++20
#include <string_view>
#include <string>
#include <vector>

template <typename T>
bool isInArray(const std::vector<T>& container,const T& value)
{
    for (const auto& item : container)
        if(value==item) return 1;
    return 0;
}



int main()
{
    std::vector<std::string_view> names{ "Alex", "Betty", "Caroline", "Dave" }; // sorted in alphabetical order
    std::string s;
    std::cout<<"Enter a name :";
    std::cin>>s;
    bool found{ isInArray(names,std::string_view(s)) };

    if(found)
    {
        std::cout<<s<<" was found";
    }
    else
    {
        std::cout<<s<<" not found";
    }
    return 0;
}