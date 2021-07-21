#include <iostream>
#include <string>
#include <vector>
#include <ctime>  
#include <cstdlib>
#include <algorithm>


namespace Utils
{
    std::string Convert_to_lowercase(std::string my_str) 
    {
        transform(my_str.begin(), my_str.end(), my_str.begin(), ::tolower);
        return my_str;
    
    }

    std::string yes_or_no(){
        while(true){
        std::string y_n;
        std::cout << "[Y|N] >";
        std::cin >> y_n;
        y_n = Utils::Convert_to_lowercase(y_n);
        if(y_n == "y" || y_n == "n"){
            return y_n;

        }else{
            std::cout << "Invalid input! Try again." << std::endl;
            continue;
        }
        }
        

    }
}

class Hand
{
    public:
        std::string choice;
        int choiceasnumber;
};


class Userhand : public Hand{
    public:
        void set_choice(){
            while(true)
            {
                std::cout<<"Choose your weapon! [rock|paper|scissors] \n >";
                std::cin >> choice;
                choice = Utils::Convert_to_lowercase(choice);
                if(choice=="rock" || choice == "paper" || choice == "scissors"){
                    break;
                }else{
                    std::cout << "Invalid input. Try again!" << std::endl;
                    continue;
                }
            
            }

        }
};


class Computerhand : public Hand{
    public:
        void set_choice()
            {
                srand(time(NULL));
                choiceasnumber = rand() % 3;
                if(choiceasnumber==0){
                    choice = "rock";
                }else if(choiceasnumber==1){
                    choice="paper";
                }else if(choiceasnumber==2){
                    choice="scissors";
                }
            }
};


int main(){
    while(true)
    {
        Userhand userhand;
        Computerhand computerhand;

        userhand.set_choice();
        computerhand.set_choice();

        std::cout << "You chose " << userhand.choice << ".\n" << "The computer chose " << computerhand.choice << ".\n";
        while(true)
        {
            if(userhand.choice == computerhand.choice){
                std::cout << "Draw!" << std::endl;
                break;
            }

            if(userhand.choice == "rock"){
                if(computerhand.choice=="paper"){
                    std::cout << "You lose!" << std::endl;
                }else if(computerhand.choice == "scissors"){
                    std::cout << "You win!" << std::endl;
                }
            }

            else if(userhand.choice == "paper"){
                if(computerhand.choice=="rock"){
                    std::cout << "You win!" << std::endl;
                }else if(computerhand.choice=="scissors"){
                    std::cout << "You lose!" << std::endl;}
            }

            else if(userhand.choice == "scissors"){
                if(computerhand.choice=="rock"){
                    std::cout << "You lose!" << std::endl;
                }else if(computerhand.choice=="paper"){
                    std::cout << "You win!" << std::endl;
                }
            }

            break;
        }

        std::cout << "Play again? ";
        std::string y_n = Utils::yes_or_no();
        if(y_n=="y"){
            continue;
        }else{
            break;
        }
    }

    return 0;
}