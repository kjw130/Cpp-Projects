#include "utils.c++"
namespace Questions
{
    std::string get_tax_year()
    {
        std::string tax_year;
        while(true)
        {

        std::cout << "Which tax year are you calculating for? [2019/2020]" << std::endl;
        std::cout << "> ";
        std::cin >> tax_year;

        if(tax_year == "2019"||tax_year == "2020")
        {
            return tax_year;
        }
        else
        {
            std::cout << "Please answer with 2019 or 2020 depending on the tax year you are calculating for." << std::endl;
        }

        }
        
    }

    std::string get_casual_or_contracted()
    {
        std::string casual_or_contracted;
        std::cout << "Are you a casual employee?" << std::endl;
        casual_or_contracted = Utils::yes_or_no();

        return casual_or_contracted;

    }


    float get_payrate(std::string cas_or_cont)
    {

        float rate_for_calculations;
        float payrate;
        std::cout << "What is your payrate?"; 
        payrate = Utils::misc_number();
        return payrate;
    }
}



// int main()
// {
    

//     return 0;
// }