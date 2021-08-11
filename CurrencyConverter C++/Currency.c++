#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

namespace Utils{
    std::string ConvertToLowercase(std::string String){
        transform(String.begin(), String.end(), String.begin(), ::tolower);
        return String;
    }

    std::string YesOrNo(){
        std::string YN;
        while(true){
            std::cout << "[Y/N] >";
            std::cin >> YN;
            YN = Utils::ConvertToLowercase(YN);
            if(YN =="y" || YN == "n"){
                return YN;
            }else{
                std::cout << "Invalid input. Please enter Y or N!" << std::endl;
            }
        }
    }

    void PrfloatVector(std::vector<std::string> VectorToPrfloat, std::string Text){
        for(float i = 0; i<VectorToPrfloat.size(); i++){
            if(i == 0){
                std::cout << Text;
            }
            if(i==VectorToPrfloat.size()-1){
                std::cout << VectorToPrfloat[i] << std::endl;
                break;
            }
            std::cout << VectorToPrfloat[i] << ", ";
        }   
    }

    std::string FindValue(std::vector<std::string> VectorToSearch, std::string ValueToCheck){
        for(float i = 0; i<VectorToSearch.size(); i++){
            if(ValueToCheck==VectorToSearch[i]){
                return "found";
            }
        }

        return "notfound";

    }

};


class Currency{
    public:
        float ConversionRateToUSD;
        float ConversionRateFromUSD;

        void SetConversionRates(float ToUSD, float FromUSD){
            ConversionRateToUSD = ToUSD;
            ConversionRateFromUSD = FromUSD;
        }

        float ConvertToUsd(float AmountForConversion){return AmountForConversion*ConversionRateToUSD;};

        float ConvertFromUsd(float AmountForConversion){return AmountForConversion*ConversionRateFromUSD;};
};


class C_USD : public Currency{};
class C_AUD : public Currency{};
class C_GBP : public Currency{};


class App{
    std::vector<std::string> AvailableCurrencies = {"aud", "usd", "gbp"};
    std::vector<std::string> AvailableCurrenciesToPrfloat = {"AUD", "USD", "GBP"};
    C_USD USD;
    C_AUD AUD;
    C_GBP GBP;
    std::string ConvertTo;
    std::string ConvertFrom;
    std::string wasfound;
    float Amount;
    float Conversion;
    float Translation;
    
    void SetRates(){
        USD.SetConversionRates(1,1);
        AUD.SetConversionRates(0.74, 1.36);
        GBP.SetConversionRates(1.39, 0.72);
    }

    void Convert(){
        
        if(ConvertTo==ConvertFrom){
            Conversion = Amount*1;
        }

        else if(ConvertTo=="usd"){
            if(ConvertFrom=="aud"){
                Conversion = AUD.ConvertToUsd(Amount);

            }else if(ConvertFrom=="gbp"){
                Conversion = GBP.ConvertToUsd(Amount);
            }

        }else if(ConvertTo=="aud"){
            if(ConvertFrom=="usd"){
                Conversion = AUD.ConvertFromUsd(Amount);

            }else if(ConvertFrom=="gbp"){
                Translation = GBP.ConvertToUsd(Amount);
                Conversion = AUD.ConvertFromUsd(Translation);
            }

        }else if(ConvertTo=="gbp"){
            if(ConvertFrom=="usd"){
                Conversion = GBP.ConvertFromUsd(Amount);

            }else if(ConvertFrom=="aud"){
                Translation = AUD.ConvertToUsd(Amount);
                Conversion = GBP.ConvertFromUsd(Translation);

            }
        }
    };

    public:
        void RunApp(){
            while(true){
                SetRates();
                std::cout << "Welcome to the currency converter!" << std::endl;
                Utils::PrfloatVector(AvailableCurrenciesToPrfloat, "The currencies avaliable are: ");

                while(true){
                    std::cout << "Which currency are you converting from?" << std::endl;
                    std::cin >> ConvertFrom;
                    ConvertFrom = Utils::ConvertToLowercase(ConvertFrom);
                    wasfound = Utils::FindValue(AvailableCurrencies, ConvertFrom);
                    if(wasfound=="notfound"){
                        std::cout << "Invalid input. Try again." << std::endl;
                        Utils::PrfloatVector(AvailableCurrenciesToPrfloat, "The currencies avaliable are: ");
                        continue;
                    }
                    break;
                }

                while(true){
                    std::cout << "Which currency would you like to convert to?" << std::endl;
                    std::cin >> ConvertTo;
                    ConvertTo = Utils::ConvertToLowercase(ConvertTo);
                    wasfound = Utils::FindValue(AvailableCurrencies, ConvertTo);
                    if(wasfound=="notfound"){
                        std::cout << "Invalid input. Try again." << std::endl;
                        Utils::PrfloatVector(AvailableCurrenciesToPrfloat, "The currencies avaliable are: ");
                        continue;
                    }
                    break;
                }

                std::cin >> Amount;

                Convert();
                std::cout << Amount << " " << ConvertFrom << " is " << Conversion << " " << ConvertTo << std::endl;

                std::cout << "Would you like to make another conversion?" << std::endl;
                std::string YN = Utils::YesOrNo();
                if(YN=="y"){
                    continue;
                }else if(YN=="n"){
                    break;
                }
            }
        }
};

int main(){
    App app;
    app.RunApp();
}
