#include <iostream>
#include <string>
#include <vector>
#include <ctime>  
#include <cstdlib>
#include <algorithm>
#include <math.h> 

namespace Utils{
    
    std::string Convert_to_lowercase(std::string my_str){
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
            }
            else{
                std::cout << "Please enter with y or n!";
                continue;
            }
        }
    }

    std::string misc_input(){
        std::string input;
        std::cin >> input;

        return input;
    }
};

class Words
{
    std::vector <std::string> words = {"golf", "surprising", "insight", "galaxy", "variation", "founder", "mount", "belt", "discussion", "tent", "speech", "them",
     "classic", "habitat", "colonial", "thing", "stir", "dramatically", "judge", "utility", "incentive", "accident", "advance", "ultimately",
      "investigation", "sequence", "philosophy", "basket", "introduction", "exchange", "overcome"};

    public:
        std::string word;
        std::string word_final;
        std::string hidden_word;

        void SetWord()
        {
            srand(time(NULL));
        
            int number = rand() % words.size();
            word = words[number];
            hidden_word = word;
        }

        void hideletters(){
            int length_of_word = word.length();
            int divide = length_of_word/4;
            divide = round(divide);
            int hide = divide;

            std::vector <char> result = {};
            std::vector <int> letters = {};
            std::vector <char> print_word = {};

            for(int i = 0; i < length_of_word; i++){
                letters.push_back(i);
            }

            int incremement;

            for(int i = 0; i <= hide; i++){
                result.push_back (word[letters[i]]);
                if(i>=hide){
                    break;
                }
            }

            for(int i = 0; i<word.size(); i++){
                
                if(result[i]==word[i]){
                    print_word.push_back(word[i]);
                }else{
                    print_word.push_back('_');
                }
            }
            
            for(int i = 0; i<print_word.size(); i++){
                word_final.push_back(print_word[i]);
            }
        }

        int findIndex(const std::vector<char> &arr, char item) {

            for (auto i = 0; i < arr.size(); ++i) {
                if (arr[i] == item)
                    return i;
            }

            return -1;
}

        void fill_gaps(char guess){
            std::vector <char> word_as_vector = {};
            std::vector <char> word_final_as_vector = {};  

            for(int i = 0; i<word.length(); i++){
                word_as_vector.push_back(word[i]);   
            }

            for(int i = 0; i<word_final.length(); i++){
                word_final_as_vector.push_back(word_final[i]);
            }
            
            int first_index = 0;
            
            for(int i = 0; i<word_as_vector.size(); i++){
                if(guess == word_as_vector[i]){
                    word_final_as_vector[i] = guess;
                } 
            }
           
            word_final.erase();

            for(int i = 0; i<word_final_as_vector.size(); i++){
                word_final=word_final+word_final_as_vector[i];
            }
            
            std::cout << word_final << std::endl;
        }
    };  


class Game
{
    int wrong_guesses = 0;
    int lifes = 5;
    
    std::string get_guess(){
        std::string guess;
        std::cout << "Guess a letter!";
        guess = Utils::misc_input();
        
        return guess;
    }

    public:

        void PlayGame()
        {
            while(true){
            wrong_guesses = 0;
            Words words;
            std::string Word;
            words.SetWord();
            words.hideletters();
            
            while(true)
            {
                std::cout << words.word_final << std::endl;
                char guess;
       
                std::cout<<"Guess a letter!" << std::endl;
                
                std::cin >> guess;
                                                  
                bool found;
            
                for(int i = 0; i<words.word.length(); i++){
                    if(words.word[i] == guess){
                        found = true;
                        break;
                    }
                    else{
                        found = false;
                    }
                }
                
                if(found==true){
                    words.fill_gaps(guess);

                }else if(found==false){
                    std::cout << "Incorrect" << std::endl;
                    wrong_guesses +=1;
                }
                std::cout << "Incorrect guesses: " << wrong_guesses << "/" << lifes << std::endl;
                
                if(wrong_guesses==lifes){
                    std::cout << "The man has been hung! Game over!" << std::endl;
                    std::cout << "The word is " << words.word << std::endl;
                    break;
                }

                if(words.word_final==words.word){
                    std::cout << "The word is " << words.word << std::endl;
                    std::cout << "You win!" << std::endl;
                    break;
                }
            }

            std::cout << "Play again? " << std::endl;
            std::string play_again = Utils::yes_or_no();
            if(play_again=="y"){
                continue;
            }
            else if(play_again == "n"){
                exit(0);
            }

        }
        }
};



int main(){
    Game game;
    game.PlayGame();
    return 0;
}

