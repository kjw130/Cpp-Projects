#include <iostream>
#include <string>
#include <algorithm>
#include "questions.c++"
#include "get_hours.c++"
#include "overtime.c++"
#include "Tax.c++"
#include <vector>

class App
{
    public:
        float total_hours; 
        float total_pay;
        void run_app()
        {
        while(true)
        {
        Payrates user_pay;
        Hours user_hours;

        std::string tax_year = Questions::get_tax_year();
        std::string casual_or_contracted = Questions::get_casual_or_contracted();

        user_pay.payrate = Questions::get_payrate(casual_or_contracted);

        if (casual_or_contracted == "y")
            {
                user_pay.rate_for_calculations = user_pay.payrate / 1.25;
                user_pay.saturday_rate = user_pay.rate_for_calculations * 0.50 + user_pay.rate_for_calculations;
                user_pay.sunday_rate = user_pay.rate_for_calculations * 0.50 + user_pay.rate_for_calculations * 0.25 + user_pay.rate_for_calculations;
            }
            else
            {
                user_pay.rate_for_calculations = user_pay.payrate;
                user_pay.saturday_rate = user_pay.payrate * 0.25 + user_pay.payrate;
                user_pay.sunday_rate = user_pay.payrate * 0.50 + user_pay.payrate;
            }

            user_pay.public_holiday_rate = user_pay.payrate*2;


        Weekdays weekday;
        float weekly_hours = weekday.hours;
        float weekday_pay = weekday.calc_pay(user_pay.payrate, weekly_hours);

        Saturday saturday;
        float saturday_hours = saturday.hours;
        float saturday_pay = saturday.calc_pay(user_pay.saturday_rate, saturday_hours);

        Sunday sunday;
        float sunday_hours = sunday.hours;
        float sunday_pay = sunday.calc_pay(user_pay.sunday_rate, sunday_hours);

        
        std::cout << "Are you working on a public holiday this week?";
        std::string pub_hol = Utils::yes_or_no();
        Publicholiday publicholiday;
        float public_holiday_hours;
        float public_holiday_pay;

        if(pub_hol=="y")
        {
            
            public_holiday_hours = publicholiday.hours;
            public_holiday_pay = publicholiday.calc_pay(user_pay.public_holiday_rate, public_holiday_hours);
        }
        else if(pub_hol == "n")
        {
            public_holiday_hours = 0;
            public_holiday_pay = 0;
        }
        
        total_hours = weekly_hours + saturday_hours + sunday_hours + public_holiday_hours;
        total_pay = weekday_pay + saturday_pay + sunday_pay + public_holiday_pay;


        Overtime overtime;
        overtime.total_hours = total_hours;
        overtime.total_pay = total_pay;
        overtime.payrate = user_pay.payrate;

        float pay = overtime.Calculateovertime(casual_or_contracted, user_pay.rate_for_calculations);    
        float year_pay = pay*52;

        CalcTaxes user_taxes;
        user_taxes.setvalues(tax_year, year_pay);

        std::cout << "You will earn $" << pay << " this week before tax." << std::endl;
        std::cout << "You will earn $" << user_taxes.weekly_pay_after_tax << " this week after tax." << std::endl;
        std::cout << "On this payrate, you will earn $" << year_pay << " a year, before tax." << std::endl;
        std::cout << "On this payrate, you will earn $" << user_taxes.pay_after_taxation << " a year, after tax." << std::endl;
        std::cout << "This calculation includes a medicare levy of $" << user_taxes.medicare << " and a tax offset of $" << user_taxes.total_off_set << std::endl;
        
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "Calculate again?" << std::endl;
        std::string restart_or_quit = Utils::yes_or_no();
        if(restart_or_quit == "y")
        {
            continue;
        }
        else if(restart_or_quit == "n")
        {
            exit(0);
        }





        }
        }

       
            
        
};






int main()
{
    App app;
    app.run_app();

}