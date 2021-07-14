
#include <string>

class Overtime
{

    public:
        
        float total_hours;
        float total_pay;
        float payrate;
        float hours_for_calculation = 0;

        
        float Calculateovertime(std::string casual, float rate_for_calculations)
        {
            float pay;
            float calculate_overtime_rate;
            float over_41_hours;
            float over41hoursrate;

            if(casual == "y")
            {
                calculate_overtime_rate = rate_for_calculations * 0.50 + rate_for_calculations * 0.25 + rate_for_calculations;
                over_41_hours = ((rate_for_calculations * 0.50 + rate_for_calculations * 0.25 + rate_for_calculations) * 3);
                over41hoursrate = rate_for_calculations * 0.25 + rate_for_calculations * 2;
            }else{
                calculate_overtime_rate = rate_for_calculations * 0.50 + rate_for_calculations;
                over_41_hours = ((rate_for_calculations * 0.50 + rate_for_calculations) * 3);
                over41hoursrate = rate_for_calculations * 2;
            }

            

            if(total_hours >= 38)
            {
                hours_for_calculation = total_hours - 38;

                while(true)
                {
                    
                    if(38 < total_hours <= 41)
                    {
                        pay = ((total_hours - 38) * (calculate_overtime_rate)) + total_pay - payrate * hours_for_calculation;
                        break;
                    }
                    else if(total_hours >= 42)
                    {
                        pay = (((total_hours - 41) * over41hoursrate) + over_41_hours) + total_pay - payrate * hours_for_calculation;
                        break;
                    }else{
                        pay = total_pay;
                        hours_for_calculation = 0;
                        break;
                    }
                }
                        
            }else{
                pay = total_pay;
            }
            return pay;
        }


};