#include <array>
#include <iostream>
#include <string_view>

struct Item
{
    int gold{};
    std::string_view name{};
    /* data */
};

template<size_t N>
void printItems(const std::array<Item,N>& arr)
{
    for(auto &i: arr)
    {
        std::cout<<"A "<< i.name
                <<" costs "<<i.gold<<" gold.\n";
    }
}

int main()
{
    constexpr std::array<Item,4> items {{
        {5,"sword"},
        {3,"dagger"},
        {2,"club"},
        {7,"spear"}
    }};

    printItems (items);

    return 0;
}