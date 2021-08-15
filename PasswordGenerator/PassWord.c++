#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

namespace Utils{
    std::string ConvertToLowercase(std::string StringToConvert){
        transform(StringToConvert.begin(), StringToConvert.end(), StringToConvert.begin(), ::tolower);
        return StringToConvert;
    }

    void PrintVector(std::vector<std::string> VectorToPrint){
        for(int i = 0; i<VectorToPrint.size(); i++){
            if(i == 0){
                std::cout << "The values in the vector are: ";
            }

            if(i == VectorToPrint.size()-1){
                std::cout << VectorToPrint[i] << std::endl;
                break;
            }
            std::cout << VectorToPrint[i] << ", ";
        }
    }

    int GetNumber(){
        int Number;
        std::cout << "Enter a number >";
        while(!(std::cin>>Number)){
            std::cout << "Invalid input. Please enter a number!" << std::endl;
            std::cout << "> ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        return Number;
        
    }

    std::string YesOrNo(){
        std::string YN;
        while(true){
            std::cout << "[Y/N] >";
            std::cin >> YN;
            YN = Utils::ConvertToLowercase(YN);
            if(YN == "y" || YN == "n"){
                return YN;
            }else{
                std::cout << "Invalid input! Please enter Y or N!" << std::endl;
            }
        }
    }
};


class Password{
    public:
        std::string password;
        std::string DoesIncludeSpecialChars;
        int AmountOfCharacters;
        int AvaliableCharacters;
        std::vector<std::string> Characters = {
            "a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z", 
            "A", "B", "C", "D", "E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z",
            "1","2","3","4","5","6","7","8","9"};

        std::vector<std::string> SpecialCharacters={"!","@","#","$","%","&"};

        void RandomiseCharacters(){
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::default_random_engine e(seed);
            std::shuffle(Characters.begin(), Characters.end(), e);
        }

        void GeneratePassword(){
            for(int i = 0; i<AmountOfCharacters; i++){
                password.append(Characters[i]);
            }
        }
};


class App{
    Password password;
    std::string ReplayApp;

    public:
        void RunApp(){
            while(true){
                std::cout << "Welcome to the password generator!" << std::endl;

                std::cout << "Do you need to include special characters in your password?" << std::endl;
                password.DoesIncludeSpecialChars = Utils::YesOrNo();

                if(password.DoesIncludeSpecialChars == "y"){
                    copy(password.SpecialCharacters.begin(), password.SpecialCharacters.end(),back_inserter(password.Characters)); 
                }

                password.AvaliableCharacters = password.Characters.size();

                while(true){
                    std::cout << "How many characters do you need in the password?" << std::endl;
                    password.AmountOfCharacters = Utils::GetNumber();
                    if(password.AmountOfCharacters > password.AvaliableCharacters){
                        std::cout << "Sorry, there are too many characters in that password." << std::endl;
                        std::cout << "Try again. You can have a maximum of "<< password.AvaliableCharacters << " characters with special characters included." << std::endl;
                        continue;
                    }else{
                        break;
                    }
                }

                password.RandomiseCharacters();
                password.GeneratePassword();

                std::cout << "Your password is: " << password.password << std::endl;
                
                std::cout << "Generate another password?" << std::endl;
                ReplayApp = Utils::YesOrNo();

                if(ReplayApp=="y"){

                    if(password.DoesIncludeSpecialChars == "y"){
                        for(int i = 6; i > 0; i--){
                            password.Characters.pop_back();
                        }
                    }
                    continue;
                }else{
                    break;
                }
            }
        }
    
};


int main(){
    App app;
    app.RunApp();
    
    return 0;
}