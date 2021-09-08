#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>
#include <sstream>
#include <ios>
#include <algorithm>

namespace Utils{
    std::string ConvertToLowercase(std::string StringForConversion){
        transform(StringForConversion.begin(), StringForConversion.end(), StringForConversion.begin(), ::tolower);
        return StringForConversion;
    }

    std::string YN(){
        while(true){
            std::string YesNo;
            std::cout << "[Y/N] >";
            std::cin >> YesNo;
            YesNo = ConvertToLowercase(YesNo);
            if(YesNo == "y" || YesNo == "n"){
                return YesNo;
            }else{
                std::cout << "Invalid input! Please enter y or n!" << std::endl;
            continue;
            }
        }
    }
};


class User{
    public:
        std::string Username;
        std::string Password;
        std::string ConfirmUsername;
        std::string ConfirmPassword;
        std::string PreExistingUser;
        std::string ChangeFrom;
      
        void ChangeDetails(std::string WhatIsChanging, std::string ToChange){
                std::ostringstream text;
                std::ifstream in_file("Accountinfo.txt");
                text << in_file.rdbuf();
                std::string str = text.str();

                if(WhatIsChanging == "username"){
                    ChangeFrom = Username;
                }else if(WhatIsChanging == "password"){
                    ChangeFrom = Password;
                }
                
                size_t pos = str.find(ChangeFrom);
                str.replace(pos, std::string(ChangeFrom).length(), ToChange);
                in_file.close();

                std::ofstream out_file("Accountinfo.txt");
                out_file << str;     
                if(WhatIsChanging == "username"){
                    Username = ToChange;
                }else if(WhatIsChanging == "password"){
                    Password = ToChange; 
                }
        }
        
        void DeleteAccount(std::string Username, std::string Password, std::string file){
            std::string line;
            std::fstream myfile;
            std::fstream temp;
            temp.open("temp.txt",std::ios::out);
            myfile.open(file.c_str());
            if (!myfile.is_open()){
                std::cout << "\n\nCould not open file: "<<file<<std::endl;
                exit;
            }

            while(getline(myfile, line))
            {
                if(line!=Username + " " + Password){
                temp << line << std::endl;
                }
            }

            myfile.close();
            temp.close();
            remove(file.c_str());
            rename("temp.txt",file.c_str());
        }
};


class Records{
    std::vector<std::string> InvalidCharacters = {
        "=", "{", "}", "(",")",
        "/",".",",","<",">",";",
        ":"," "
    };

    bool DoesFileExist (const std::string& name) {
        std::ifstream f(name.c_str());
        return f.good();
    }   

    public:

        bool IsValidDetails(std::string Username, std::string Password){
            std::string ToCheck;
            
            for(int i = 0; i<2; i++){
                if(i==0){
                    ToCheck = Username;
                }else{
                    ToCheck = Password;
                }

                for(int y = 0; y<InvalidCharacters.size(); y++){
                    if(ToCheck.find(InvalidCharacters[y]) < (ToCheck.length()+100)){
                        return false;
                    }
                }
            }

            if(Username=="Username" || Username == "username" || Password=="Password" || Password == "password"){
                return false;
            }else{
                return true;
            }
        }

        bool IsDuplicate(std::string Username){
            std::fstream file;
            std::string word, t, q ,filename;
            filename = "AccountInfo.txt";
            file.open(filename.c_str());
            bool username = true;
            bool password;
            while(file >> word){
                if(word == Username && username == true){
                    return true;
                }
                if(username==true){
                    username = false; 
                    password = true;
                    continue;
                }
                else if (password==true){
                    username = true;
                    password = false;
                }
            }
            return false;
        }
       
        bool CheckLoginDetails(std::string Username, std::string Password){
            bool UsernameFound = false;
            bool PasswordFound = false;

            std::fstream file;
            std::string word, t, q ,filename;

            filename = "AccountInfo.txt";

            file.open(filename.c_str());

            while(file >> word){
                if(UsernameFound==true){
                    if(word==Password){
                        PasswordFound = true;
                        break;
                    }else{
                        PasswordFound = false;
                        UsernameFound = false;
                    }
                }
                else if(word == Username){
                    UsernameFound = true;
                }
            }
            if(UsernameFound == true && PasswordFound == true){
                return true;
            }else{
                return false;
            }
        }

        void AddUserInformation(std::string Username, std::string Password){
            std::vector <std::string> words;
            std::fstream f;
            std::ofstream fout;
            std::ifstream fin;
            bool DidFileExist = DoesFileExist("AccountInfo.txt");
            fout.open("AccountInfo.txt",std::ios::app);
            fin.open("AccountInfo.txt");

            if(fin.is_open()){
                if(DidFileExist==0){
                fout << "Username, Password" << "\n";
                fout << "\n" << Username << " " << Password <<"\n";
                }else{
                    fout << "\n" << Username << " " << Password <<"\n";
                }
            }
            fin.close();
            fout.close();
            std::string word;
            f.open("AccountInfo.txt");
        }
};


class App{
    User user;
    Records records;
    std::string UserOptions;
    std::string YN;
    public:
    
        void RunApp(){
            
            std::cout << "Welcome. Are you already a user?" << std::endl;
                user.PreExistingUser = Utils::YN();
                while(true){

                if(user.PreExistingUser=="y"){
                        std::cout << "Welcome back!" << std::endl;
                        std::cout << "Enter your username\n >";
                        std::cin >> user.Username;
                        std::cout << "Enter your password\n >";
                        std::cin >> user.Password;
                        
                    if(records.CheckLoginDetails(user.Username, user.Password)==true){
                        std::cout << "You have successfully logged in!" << std::endl;

                        while(true){
                            std::cout << "Do you want to change your details, delete account or log out?" << std::endl;
                            std::cout << "[change|delete|logout] >";
                            std::cin >> UserOptions;

                            UserOptions = Utils::ConvertToLowercase(UserOptions);

                            if(UserOptions=="change"){
                                std::cout << "Would you like to change your username change your password or cancel?" << std::endl;
                                while(true){
                                    std::cout << "[username|password|cancel] >";
                                    std::cin >> UserOptions;
                                    std::cout << std::endl;
                        
                                    UserOptions = Utils::ConvertToLowercase(UserOptions);

                                    if(UserOptions=="username"){
                                        while(true){
                                            std::string NewUsername;
                                            std::cout << "What would you like to change your username to? >";
                                            std::cin >> NewUsername;

                                            std::cout << "Please re-enter your new username for confirmation." << std::endl;
                                            std::cin >> user.ConfirmUsername;
                                            if(NewUsername == user.ConfirmUsername){
                                                user.ChangeDetails("username", NewUsername);
                                                std::cout << "Success!" << std::endl;
                                                break;
                                            }

                                            else if(NewUsername != user.ConfirmUsername){
                                                std::cout << "Error! Usernames don't match. Try again?" << std::endl;
                                                YN = Utils::YN();
                                                if(YN == "y"){
                                                    continue;
                                                }else{
                                                    break;
                                                }                                                
                                            }                                                                                        
                                        }

                                    }else if(UserOptions == "password"){
                                        while(true){                                       
                                            std::string NewPassword;
                                            std::cout << "What would you like to change your password to?";
                                            std::cin >> NewPassword;
                                            if(records.IsValidDetails(user.Username, NewPassword)==false){
                                                std::cout << "Error! Invalid password. Try again." << std::endl;
                                                continue;
                                            }

                                            user.ChangeDetails("password", NewPassword);
                                            std::cout << "Success!" << std::endl;
                                            break;
                                        }

                                        break;
                                    
                                    }else if(UserOptions == "cancel"){
                                        break;
                                    }else{
                                        std::cout << "Invalid input. Try again." << std::endl;
                                        continue;
                                    }
                            }

                            }else if(UserOptions == "delete"){
                                std::cout << "Are you sure that you want to delete your account? Your account is unrecoverable." << std::endl;
                                YN = Utils::YN();

                                if(YN == "y"){
                                    user.DeleteAccount(user.Username, user.Password, "Accountinfo.txt");
                                    break;

                                }else{ 
                                    std::cout << "Account has not been deleted. Returning to main menu." << std::endl;
                                    continue;
                                }
                                
                            }else if(UserOptions == "logout"){
                                std::cout << "Successfully logged out!" << std::endl;
                                break;
                            }else{
                                std::cout << "Invalid input. Please try again." << std::endl;
                                continue;
                            } 
                        }

                    }else{
                        std::cout << "Authentication failed!" << std::endl;
                        std::cout << "Try to log in again?";
                        YN = Utils::YN();
                        if(YN == "y"){
                            continue;
                        }else{
                            break;
                        }
                    }
                    
                }else if(user.PreExistingUser == "n"){
                    bool ValidAccount = false;
                        if(ValidAccount==true){
                            break;
                        }
                        
                        std::cout << "Welcome! To enter, you need to create an account." << std::endl;
                        while(true){

                            while(true){
                                    std::cout << "Enter a username!\n >";
                                    std::cin >> user.Username;
                                    
                                    if(records.IsDuplicate(user.Username)==true){
                                            std::cout << "Username already exists! Try again with a new username." << std::endl;
                                            continue;
                                    }else if(records.IsDuplicate(user.Username)==false){
                                        break;
                                    }
                                }
                                while(true){
                                    std::cout << "Enter a password!\n >";
                                    std::cin >> user.Password;

                                    std::cout << "Reconfirm password\n >";
                                    std::cin >> user.ConfirmPassword;

                                    if(records.IsValidDetails(user.Username, user.Password)==false){
                                        std::cout << "Either your username or password is invalid. Please re-enter details." << std::endl;
                                        break;
                                    }

                                    if(user.Password == user.ConfirmPassword){
                                        records.AddUserInformation(user.Username, user.Password);
                                        std::cout << "Congratulations! Your account has successfully been created!" << std::endl;
                                        break;
                                    }else{
                                        std::cout << "Error! Passwords don't match. Try again." << std::endl;
                                        continue;
                                    }
                                }    
                                break; 
                    }
                    break;

                }
            break;
        }
    }
};


int main(){
    while(true){
        App app;
        app.RunApp();
    }
    return 0;
}