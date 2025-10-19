    #include <array>
    #include <iostream>
    #include <string_view>

    struct animal
    {
        std::string_view name{};
        int numOfLegs{};
        std::string_view sound{};
        /* data */
    };

    namespace Animal
    {
        enum Type
        {
            chicken, 
            dog, 
            cat, 
            elephant, 
            duck,
            snake,
            maxAnimal
        };
        //using namespace std::string_view_literals;
        constexpr std::array<animal, 6> animals {{ // note double braces
            // { "chicken"sv, 2, "o o o"sv},
            // { "dog"sv, 4, "woft"sv },
            // { "cat"sv, 4, "mew"sv },
            // { "elephant"sv, 4, "paw"sv },
            // { "duck"sv, 2, "quag"sv },
            // { "snake"sv, 0, "phi"sv }
            { "chicken", 2, "o o o"},
            { "dog", 4, "woft" },
            { "cat", 4, "mew" },
            { "elephant", 4, "paw" },
            { "duck", 2, "quag" },
            { "snake", 0, "phi" }
        }};

        constexpr std::array types {
            chicken, 
            dog, 
            cat, 
            elephant, 
            duck,
            snake,
        };
        static_assert(std::size(types) == Animal::maxAnimal);    
        static_assert(std::size(animals) == Animal::maxAnimal);

    };


    std::istream& operator>> (std::istream& in, Animal::Type& animal)
    {
        std::string input {};
        std::getline(in >> std::ws, input);

        for (std::size_t index=0; index < Animal::animals.size(); ++index)
        {
            if (input == Animal::animals[index].name)
            {
                // If we found a matching name, we can get the enumerator value based on its index
                animal = static_cast<Animal::Type>(index);
                return in;
            }
        }
        in.setstate(std::ios_base::failbit);
        return in;
    }


    constexpr std::string_view getAnimalName(Animal::Type animal)
    {
        return Animal::animals[animal].name;
    }

// Teach operator<< how to print a Color
// std::ostream is the type of std::cout
// The return type and parameter type are references (to prevent copies from being made)!
    std::ostream& operator<<(std::ostream& out, Animal::Type animal)
    {
        return out << getAnimalName(animal);
    }

    void printAnimalData(Animal::Type a)
    {
        std::cout << "A " << a << " has "<<Animal::animals[a].numOfLegs
                <<" legs and say "<<Animal::animals[a].sound<<"\n";
    }


    int main()
    {
        Animal::Type animal {};
        std::cout<<"enter a animal: ";
        std::cin>>animal;

        if (!std::cin)
        {
            std::cin.clear();
            std::cout << "That animal couldn't be found.\n";
            animal = Animal::maxAnimal;
        }
        else
        {
            std::cout << "A " << animal << " has "<<Animal::animals[animal].numOfLegs
            <<" legs and say "<<Animal::animals[animal].sound<<"\n";
            
        }

        std::cout<<"Here is the data for the rest of the animals:\n";
        for(auto c:Animal::types)
            {
                if(animal!=c)
                {
                    printAnimalData(c);
                }
                
            }

        return 0;
    }
