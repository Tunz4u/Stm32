#include<iostream>
#include <string_view>
#include<string>
#include <limits>

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // cin.ignore(int x, until meet \n) ignore all untill meet\n
}
int main()
{   

    int bornYear{};
    std::cout<<"nhap nam sinh cua ban:";
    std::cin>>bornYear;
    ignoreLine();

    std::string name{};
    std::cout<<"nhap ten cua ban:";
    std::getline(std::cin,name);

    std::cout<<"ban la "<<name<<". Ban nam nay "<<2025-bornYear<<" tuoi";
    
    return 0;
}