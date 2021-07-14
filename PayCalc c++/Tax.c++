#include <vector>
class Tax
{
    public:
        std::vector<int> brackets;
        std::vector<float> rates;
        std::vector<int> set_tax;
        float tax;

        void set_taxrates(std::string tax_year, float year_pay)
        {
            if (tax_year == "2019")
            {
                brackets = {18200, 37000, 90000, 180000};
                rates = {0.19, 0.325, 0.37, 0.45};
                set_tax = {3572, 20797, 54097};
            }

            else if (tax_year == "2020")
            {
                brackets = {18200, 45000, 120000, 180000};
                rates = {0.19, 0.325, 0.37, 0.45};
                set_tax = {5092, 29467, 51667};
            }

            if (year_pay <= (brackets[0]))
            {
                tax = 0;
            }
            else if ( (brackets[0]) < year_pay <= (brackets[1]) )
            {
                tax = (year_pay - (brackets[0])) * (rates[0]);
            }

            else if ((brackets[1]) <= year_pay <= (brackets[2]))
            {
                tax = (year_pay - (brackets[1])) * (rates[1]) + (set_tax[0]);
            }
            else if ( (brackets[2]) < year_pay <= (brackets[3]) )
            {
                tax = (year_pay - (brackets[2])) * (rates[2]) + (set_tax[1]);
            }
            else if ( year_pay > (brackets[3]) )
            {
                tax = (year_pay - (brackets[3])) * (rates[3]) + (set_tax[2]);
            }
        }

};


class MedicareLevy
{
    public:
        float medicarelevy;

        void set_medicarelevy(float year_pay)
        {
            if (year_pay >= 28501){
                medicarelevy = year_pay * 0.02;
            }
            else if(year_pay <= 28500)
            {
                medicarelevy = 0;
            }

        }
};


class Offsets
{
    public:
        float maximum_off_set;
        float off_set_rate;
        float low_off_set;
        float middle_off_set;
        float total_offset = low_off_set + middle_off_set;

    
        void offSetMaximum(){
            std::string tax_year;
        
            if(tax_year == "2019")
            {
                maximum_off_set = 445;
                off_set_rate = 0.0165;
            }
                
            else if(tax_year == "2020")
            {
                maximum_off_set = 700;
                off_set_rate = 0.05;
            }
           
        }


        void low_tax_off_set(float year_pay, float tax)
        {
            if(year_pay <= 18200)
            {
                low_off_set = 0;
            }

            else if( 18200 < year_pay <= 37500){

                if (tax >= maximum_off_set)
                {
                    low_off_set = maximum_off_set;
                }
                else if( tax <= maximum_off_set)
                {
                    low_off_set = tax;
                }
            }

            else if(37501 <= year_pay <= 45000)
            {
                low_off_set = maximum_off_set - ((year_pay - 37500) * off_set_rate);

            }else if( 45001 <= year_pay <= 66667)
            {
                low_off_set = 325 - ((year_pay - 45000) * 0.015);
            }

            else if( year_pay >= 66668)
            {
                low_off_set = 0;
            }
        }
                
        void middle_income_offset(float year_pay, float tax)
        {
            if(year_pay <= 18200)
                middle_off_set = 0;

            else if(18200 < year_pay <= 37000)
            {
                if(tax <= maximum_off_set){
                    middle_off_set = 0;

                }else if( maximum_off_set < tax < 955){
                    middle_off_set = tax - maximum_off_set;
                }

                else if (tax >= 955)
                {
                    middle_off_set = 255;
                }

            }else if (37001 <= year_pay <= 48000){

            
                middle_off_set = 255 + ((year_pay - 37000) * 0.075);
            }
            else if (48001 <= year_pay <= 90000){
                middle_off_set = 1080;
            }

            else if (90001 <= year_pay <= 126000){
                middle_off_set = 1080 - ((year_pay - 90001) * 0.03);
            }

            else if (year_pay >= 126000){
                middle_off_set = 0;
            }

        }
};


class CalcTaxes
{
    public:
        Tax taxes;
        MedicareLevy medicare_levy;
        Offsets taxoffsets;
        float pay_after_taxation;
        float weekly_pay_after_tax;
        float medicare;
        float total_off_set;
        
        void setvalues(std::string tax_year, float year_pay)
        {
            taxes.set_taxrates(tax_year, year_pay);           
            medicare_levy.set_medicarelevy(year_pay);             
            medicare = medicare_levy.medicarelevy;      
            taxoffsets.offSetMaximum();
            taxoffsets.low_tax_off_set(year_pay, taxes.tax);
            taxoffsets.middle_income_offset(year_pay, taxes.tax);

            pay_after_taxation = year_pay - taxes.tax - medicare + taxoffsets.total_offset;
            weekly_pay_after_tax = pay_after_taxation/52;

        }
 
};