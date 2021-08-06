#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

namespace Utils
{
    std::string convert_to_lowercase(std::string my_str) 
    {
        transform(my_str.begin(), my_str.end(), my_str.begin(), ::tolower);
        return my_str;
    }

    std::string yes_or_no()
    {
        std::string y_n;
        while(true)
        {
            std::cout << "[Y/N] >";
            std::cin >> y_n;
            y_n = Utils::convert_to_lowercase(y_n);
            if(y_n == "y" || y_n == "n")
            {
                return y_n;
            }
            else{
                std::cout << "Please enter y or n!" << std::endl;
            }
        }
    }
};



class Hand
{
    public:
        std::vector<int> cards;

        void ViewCards(std::vector<int> cards, std::string which_player)
        {
            for(int i = 0; i<cards.size(); i++)
            {
                if(i==0)
                {
                    if(which_player=="better")
                    {
                        std::cout<< "The cards in your hand are: ";
                    }

                    else if(which_player=="dealer")
                    {
                        std::cout<< "The cards in the dealers hand are: ";
                    }
                }
                
                if(i==(cards.size() - 1))
                {
                    std::cout << cards[i] << std::endl;
                    break;
                }
                std::cout << cards[i] << ", ";

            }
        }

        int CountCards(std::vector<int> total_cards)
            {
                int base;
                for (int i = 0; i < total_cards.size(); i++)
                {
                    if(i==0)
                    {
                        base = total_cards[i];
                    }

                    else if(i>0)
                    {
                        
                        base = base + total_cards[i];
                    }
                
                }
                return base;
            }
};



class Player
{
    public:
        Hand playershand;
        int DrawAce(std::vector<int> hand, int card, std::string which_player)
            {
                int one_or_eleven;

                std::cout << "You have drawn an ace!" << std::endl;

                if(which_player=="dealer")
                {
                    int DealerSum = playershand.CountCards(playershand.cards);

                    if(DealerSum < 11)
                    {
                        card = 11;
                    }
                    else
                    {
                        card = 1;
                    }
                }

                else if(which_player=="better"){

                    while(true)
                    {
                        std::cout << "Do you want the ace to equal one or eleven?\n >";
                        std::cin >> one_or_eleven;
                        
                        if (one_or_eleven == 1 || one_or_eleven == 11)
                        {

                            if (one_or_eleven == 11)
                            {
                                card = 11;
                            }    
                            else if (one_or_eleven == 1)
                            {
                                card = 1;
                            }
                            break;
                            

                        }else{
                            std::cout << "Please type either one or eleven!" << std::endl;
                        }
                    }
                }

                return card;
            }

};


class Deck
{
    public:
        std::vector<int> Cards = {1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,8,9,9,9,9,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10};

        void ShuffleDeck()
        {
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::default_random_engine e(seed);
            std::shuffle(Cards.begin(), Cards.end(), e);
        }  

        void DrawCard()
        {
            Cards.erase(Cards.begin());
        }
};


class Dealer : public Player
{  
    public:
        Deck deck;

        std::string DealerDrawOrPass(std::vector<int> dealercards)
        {
            int sum_of_hand = playershand.CountCards(dealercards);
            std::string choice;

            if (sum_of_hand > 16)
            {
                choice = ("pass");
            }
            if(sum_of_hand <= 16)
            {
                choice = ("hit");
           }
            return choice;
        } 

        std::vector<int> DealCards(int HowManyDraws, std::vector<int> hand, std::string which_player)
        {
            int ReserveCard;
            for(int Draws = 0; Draws<HowManyDraws; Draws++){
                
                int card = (deck.Cards[Draws]);
                deck.DrawCard();

                if(HowManyDraws==2&&Draws==0){
                    ReserveCard = card;
                }
                
                if(which_player == "better" && card == 1){
                    card = DrawAce(hand, card, "better");
                }

                else if (which_player == "dealer" && card == 1)
                {
                    card = DrawAce(hand, card, "dealer");
                }

                hand.push_back(card);

                if(which_player=="better"&&Draws==HowManyDraws-1){
                    std::cout << "The dealer has drawn!" << std::endl;
                        if(HowManyDraws==1){
                            std::cout << "Your new card is: " << card << std::endl;
                        }else if(HowManyDraws==2){
                            std::cout << "Your starting cards are: " << card << ", " << ReserveCard << std::endl;
                        }
                }
            }
            return hand;
        }        
        
};


class Better : public Player
{
    public:
        std::string AskBetter()
            {
                std::string hit_or_pass;

                while (true){
                    std::cout << "Hit or pass?\n [HIT/PASS] >" << std::endl;
                    std::cin >> hit_or_pass;

                    if(hit_or_pass == "hit" || hit_or_pass == "pass"){
                        return hit_or_pass;
                    }
                    else{
                        std::cout << "Not an option. Type hit or pass!" << std::endl;
                    }
                }
            }
};


class App
{
    Dealer dealer;
    Better better;

    public:
        
        std::string play_again(){
            
            while (true){
                std::cout << "Play again?" << std::endl;
                std::cout << "[y/n] >";
                std::string y_or_n = Utils::yes_or_no();

                if (y_or_n == "y" || y_or_n == "n"){
                    return y_or_n;
                }
                else{
                    std::cout << "Please answer y or n!" << std::endl;
                }
            }
        }

        void main(){
            while (true)
            {
                std::cout << "Welcome to blackjack." << std::endl;
               
                std::cout << "The dealer is drawing. Get ready" << std::endl;

                dealer.deck.ShuffleDeck();
                
                int HowManyDraws = 2;
                
                better.playershand.cards = dealer.DealCards(HowManyDraws, better.playershand.cards, "better");
                dealer.playershand.cards = dealer.DealCards(HowManyDraws, dealer.playershand.cards, "dealer");
                std::string DealersChoice;
                std::string BettersChoice;
                
                bool FirstLoop = true;
                while(true){
                    if(FirstLoop==false){
                    better.playershand.ViewCards(better.playershand.cards, "better");
                    }
                    FirstLoop=false;

                    int BetterSum = better.playershand.CountCards(better.playershand.cards);
                    std::cout << "The sum of your hand is: " << BetterSum << std::endl;

                    BettersChoice = better.AskBetter();
                    DealersChoice = dealer.DealerDrawOrPass(dealer.playershand.cards);

                    HowManyDraws = 1;

                    int DealerSum = dealer.playershand.CountCards(dealer.playershand.cards);

                    if (BettersChoice == "hit" || DealersChoice == "hit"){
                            
                            if(BettersChoice == "hit")
                            {
                                better.playershand.cards = dealer.DealCards(HowManyDraws, better.playershand.cards, "better");
                            }

                            if (DealersChoice == "hit")
                            {                               
                                dealer.playershand.cards = dealer.DealCards(HowManyDraws, dealer.playershand.cards, "dealer");
                            }
                            
                            BetterSum = better.playershand.CountCards(better.playershand.cards);
                            DealerSum = dealer.playershand.CountCards(dealer.playershand.cards);

                        }

                    if (BetterSum > 21 || DealerSum > 21)
                    {
                        better.playershand.ViewCards(better.playershand.cards, "better");
                        std::cout << "Your sum is "<< BetterSum << std::endl;
                        std::cout << "The dealers sum is " << DealerSum << std::endl;

                        if (BetterSum > 21 && DealerSum > 21){
                            if(BetterSum > DealerSum){
                                std::cout << "You lose!" << std::endl;
                            }
                            else if (BetterSum < DealerSum){
                                std::cout <<"You Win! " << std::endl;
                            }
                            else if (BetterSum == DealerSum){
                                std::cout << "Draw!" << std::endl;
                            }
                            break;

                        }
                        else if( BetterSum > 21)
                        {
                            std::cout << "You lose!" << std::endl;
                        }
                        else if(DealerSum > 21)
                        {
                            std::cout << "You win!" << std::endl;
                        }
                        break;
                    }

                    else if (BettersChoice == "pass" && DealersChoice == "pass")
                    {

                        std::cout << "Your sum is " << BetterSum << std::endl;
                        
                        std::cout << "The dealers sum is " << DealerSum << std::endl;

                        if (BetterSum > 21)
                        {
                            std::cout << "You lose!"<< std::endl;
                        }

                        else if( DealerSum > 21)
                        {
                            std::cout << "You win!" << std::endl;
                        }
                        else if (BetterSum && DealerSum <= 21)
                        {

                            if(BetterSum > DealerSum)
                            {
                               std::cout << "You win!" << std::endl;
                            }
                            
                            else if (BetterSum < DealerSum)
                            {
                                std::cout << "You lose!" << std::endl;
                            }
                            else if( BetterSum == DealerSum)
                            {
                                std::cout << "Tie!" << std::endl;
                            }
                        }
                        break;
                    }
                    
                }
                std::cout << "play again? ";
                std::string y_or_n = Utils::yes_or_no();

                if (y_or_n == "y")
                {
                    break;
                }
                if (y_or_n == "n")
                {
                    exit_app();
                }
            }
        }
    void exit_app(){
        exit(0);
    };
};


int main()
{
    while (true){
    App app;
    app.main();
    }
    return 0;
}