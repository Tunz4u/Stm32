#include<iostream>
#include<string_view>
#include <array>
#include "Random.h"
#include <limits>

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // cin.ignore(int x, until meet \n) ignore all untill meet\n
}

bool hasUnextractedInput() // Extraction succeeds but with extraneous input
{
    // std::cout <<"1";
    return !std::cin.eof() && std::cin.peek() != '\n';
}

// returns true if std::cin has unextracted input on the current line, false otherwise



namespace Potion
{
    enum Type
    {
        healing,
        mana,
        speed,
        invisibility,
        maxType,
    };
    constexpr std::array types{healing,mana,speed,invisibility};
    constexpr std::array costs {20,30,12,50};
    constexpr std::array <std::string_view,maxType> names{
        "healing",
        "mana",
        "speed",
        "invisibility"
    };
    

    static_assert(std::size(types)==maxType);
    static_assert(std::size(costs)==maxType);
    static_assert(std::size(names)==maxType);
}






int charNumToInt(char c) {
    return c - '0';
}

Potion::Type selection()
{
    char x{};
    while (true) // Loop until user enters a valid input
    {
        std::cout << "Enter the number of the potion you'd like to buy, or 'q' to quit: ";
        
        std::cin >> x;
        if(x=='q')return Potion::maxType;
        int y=charNumToInt(x);

        if (hasUnextractedInput())
        {
            std::cout<<"Extraneous input. Try again!\n"; 
            ignoreLine(); // remove extraneous input
            continue;
        }
        
        ignoreLine();     // And remove the bad input
        for(auto c:Potion::types)
        {
            if(y==c)
            {
                return static_cast<Potion::Type> (y); 
            }
        }
        std::cout<<"Only from 0 to 3  Try again: \n";
                     // Return it (otherwise, we go back to top of loop)
    }
}



class Player
{
private:
    static constexpr int s_minStartingGold { 80 };
    static constexpr int s_maxStartingGold { 120 };
    std::string m_name{};
    int m_gold{};
    std::array<int,Potion::maxType> m_inventory{};
public:
    explicit Player(std::string name):
        m_name{name},
        m_gold{Random::get(s_minStartingGold,s_maxStartingGold)}{}
    int gold() const {return m_gold;}
    int inventory(Potion::Type p)const{return m_inventory[p];}

    bool buyInventory(Potion::Type p)
    {
        
        if(m_gold<Potion::costs[p]) 
        {
            std::cout<<"You can not afford that.\n";
            return false;
        }
        m_gold -= Potion::costs[p];
        m_inventory[p]++;
        return true;
    }

    void printInventory()
    {
        std::cout<<"Your inventory contains:\n";
        for(auto&c:Potion::types)
        {
            if(inventory(c)==0) continue;
            std::cout<<inventory(c)
            <<" x potion of "<<Potion::names[c]<<" \n";
        } 
        std::cout<<"You escaped with "
        <<gold()<<" gold left.\n";
    }

};

void shop(Player& player)
{
    Potion::Type userInp{};
    while (true)
    {   
        //// print list potion
        std::cout << "Here is our selection for today:\n";
        for(auto&index :Potion::types)
        {   
        std::cout<<index<<") "<<Potion::names[index]<<" costs "<<Potion::costs[index]<<" gold\n" ;
        }
        ////

        userInp=selection();
        if(userInp==Potion::maxType)
        {   
            std::cout<<"bye\n";
            break;
        }
        if(!player.buyInventory(userInp))
        {
            std::cout<<"You have "<<player.gold()<<" gold left.\n";
            continue;
        } 

        std::cout<<"You purchased a potion of "<<Potion::names[userInp]<<". You have "
        <<player.gold()<<" gold left.\n";
    }

}


int main ()
{   
    std::cout << "Welcome to Roscoe's potion emporium!\n";
    std::cout << "Enter your name: ";

    std::string name{};
    Player player { name };
    std::getline(std::cin >> std::ws, name); // read a full line of text into name
    std::cout << "Hello, " << name 
    << ", you have " << player.gold() << " gold.\n\n"; 


    shop(player);
    player.printInventory();

    
    std::cout << "Thanks for shopping at Roscoe's potion emporium!\n";
    return 0;

}