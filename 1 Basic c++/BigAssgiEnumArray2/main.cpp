#include <iostream>
#include <array>
#include<string_view>
#include <algorithm> // for std::shuffle
#include "Random.h"  // for Random::mt
#include <cassert> 


namespace Settings
{
    // Maximum score before losing.
    constexpr int bust{ 21 };

    // Minium score that the dealer has to have.
    constexpr int dealerStopsAt{ 17 };

    
}
// An alias template for a two-dimensional std::array
template <typename T, std::size_t Row, std::size_t Col>
using Array2d = std::array<std::array<T, Col>, Row>;

struct Card
{
    enum Rank
    {
        rank_ace,
        rank_2,
        rank_3,
        rank_4,
        rank_5,
        rank_6,
        rank_7,
        rank_8,
        rank_9,
        rank_10,
        rank_jack,
        rank_queen,
        rank_king,

        max_ranks,
    };

    enum Suit
    {
        suit_club,
        suit_diamond,
        suit_heart,
        suit_spade,

        max_suits,
    };

    Rank rank{};
    Suit suit{};

    static constexpr std::array allRanks{
    rank_ace,
    rank_2,
    rank_3,
    rank_4,
    rank_5,
    rank_6,
    rank_7,
    rank_8,
    rank_9,
    rank_10,
    rank_jack,
    rank_queen,
    rank_king
    };
    static_assert(std::size(allRanks)==max_ranks);



    static constexpr std::array allSuits{
    suit_club,
    suit_diamond,
    suit_heart,
    suit_spade
    };
    static_assert(std::size(allSuits)==max_suits);



    // static constexpr Array2d<std::string_view,max_suits,max_ranks> allCards{{
    // {"AC","2C","3C","4C","5C","6C","7C","8C","9C","TC","JC","QC","KC"},
    // {"AD","2D","3D","4D","5D","6D","7D","8D","9D","TD","JD","QD","KD"},
    // {"AH","2H","3H","4H","5H","6H","7H","8H","9H","TH","JH","QH","KH"},
    // {"AS","2S","3S","4S","5S","6S","7S","8S","9S","TS","JS","QS","KS"}
    // }};


    friend  std::ostream& operator<<(std::ostream& out, const Card &card)
    {

        //out <<Card::allCards[card.suit][card.rank] ;

        static constexpr std::array ranks { 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K' };
        static constexpr std::array suits { 'C', 'D', 'H', 'S' };
        assert(card.rank<max_ranks &&"max rank");
        assert(card.suit<max_suits &&"max suit");
        out << ranks[card.rank] << suits[card.suit];// print your card rank and suit here
        
        return out;
    }

    int value() const
    {
        static constexpr std::array rankValues { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };
        return rankValues[rank];
    }

};



class Deck
{
private:
    /* data */
    std::array <Card,52> cards{};
    int currentcardindex {};

public:
    Deck(){
        size_t count{};
        for (auto suit : Card::allSuits)
            for (auto rank : Card::allRanks)
            {
                cards[count++]=Card { rank, suit};
            }

    }

    void printAllCardIndeck()
    {
        size_t count{};
        for(count=0;count<52;)
        {
            std::cout<<cards[count++]<<" ";
        } 
        std::cout<<"\n";
    }
    

    Card dealCard()
    {
        //std::cout<<cards[currentcardindex]<<" ";
        assert(currentcardindex < 52 && "Deck::dealCard ran out of cards");
        return cards[currentcardindex++];
    }


    void shuffle()
    {
        std::shuffle(cards.begin(), cards.end(), Random::mt);
        currentcardindex=0;
    }



};

struct Player
{
    int score{};
    int aceCount{};
};

bool dealerTurn(Deck& deck,Player& dealer )
{   

    Card card{};
    int hitTime{};
    while (dealer.score<Settings::dealerStopsAt&&hitTime<4)
    {
        /* code */
        hitTime++;
        card=deck.dealCard();
        dealer.score+=card.value();
        if(card.value()==11) dealer.aceCount++;
        if(dealer.aceCount>0&&dealer.score>Settings::bust)
        {
            dealer.score-=10;
            dealer.aceCount--;
        }
        std::cout<<"Dealer flip a "<<card<< ". They now have: "<<dealer.score<<"\n";
    
    }

    if(dealer.score>Settings::bust) 
    {
        std::cout<<"The dealer went bust!\n";
        return true;
    }

    return false;

}

bool playerWantsHit()
{
    char input{};
    while (true)
    {
        /* code */
        std::cout << "(h) to hit, or (s) to stand: ";
        std::cin>>input;
        switch (input)
        {
            case 'h':
                return true;
            case 's':
                return false;   
        }
    }
    
}

bool playerTurn(Deck& deck,Player& player )
{   

    Card card{};
    char input{};
    int hitTime{};

    while(player.score<Settings::bust&&playerWantsHit()&&hitTime<3) 
    {

        hitTime++;
        card=deck.dealCard();
        player.score+=card.value();
        if(card.value()==11) player.aceCount++;
        if(player.aceCount>0&&player.score>Settings::bust)
        {
            player.score-=10;
            player.aceCount--;
        }

        std::cout<<"You were dealt "<<card<< ". Now you have: "<<player.score<<"\n";

    };


    if(player.score>Settings::bust) 
    {
        std::cout<<"You went bust!\n";
        return true;
    }

    return false;
}

void checkAce(Player& player,Card& card)
{
    if (card.value()==11)
    {
        player.aceCount++;
    }
    player.score+=card.value();
}

enum Result
{
    loss,
    win,
    draw,
};

Result playBlackjack()
{
    Deck deck{};

    deck.shuffle();
     
    Card dealerCard{deck.dealCard()};
    Player dealer{dealerCard.value()};
    std::cout << "The dealer is showing " <<dealerCard<<" :" <<dealer.score << " \n";

    Player player {};
    Card playerCard1{deck.dealCard()};
    checkAce(player,playerCard1);
    Card playerCard2{deck.dealCard()};
    checkAce(player,playerCard2);
    
    if (player.score>Settings::bust&&player.aceCount>0)
    {
        player.aceCount--;
        player.score-=10;
    }
    

    std::cout << "You have " << playerCard1 << " and "<<playerCard2<<" : "<<player.score<<"\n";

    if(playerTurn(deck,player)||player.score<dealer.score) return loss;
    if(dealerTurn(deck,dealer)||player.score>dealer.score) return win;
    if(player.score==dealer.score) return draw;
    return draw;

}


    // Put this line in your shuffle function to shuffle m_cards using the Random::mt Mersenne Twister
    // This will rearrange all the Cards in the deck randomly

    
int main()
{
    Result result {playBlackjack()};
    if (result==win)
    {
        std::cout << "You win!\n";
    }
    else if (result==loss)
    {
        std::cout << "You lose!\n";
    }
    else
    {
        std::cout<<"You draw!\n";
    }

    return 0;
}
