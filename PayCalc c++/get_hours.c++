class Payrates
{
    public:
        float payrate;
        float rate_for_calculations;
        float saturday_rate;
        float sunday_rate;
        float public_holiday_rate;
  
};

class Hours
{
    public:
        float pay;

        int get_hours(std::string prompt)
        {
            
            std::cout << prompt << std::endl;
            float hours = Utils::misc_number();
            return hours;
        }

        int calc_pay(float payrate, float hours)
        {
            float pay = hours*payrate;
            return pay;
        };
};


class Weekdays : public Hours
{
    public:
        std::string prompt = "How many hours are you working during the week?";
        float hours = get_hours(prompt);
};


class Saturday : public Hours
{
    public:
        std::string prompt = "How many hours are you working on saturday?";
        float hours = get_hours(prompt);
};


class Sunday : public Hours
{
    public:
        std::string prompt = "How many hours are you working on sunday?";
        float hours = get_hours(prompt);
};


class Publicholiday : public Hours
{
    public:
        std::string prompt = "How many hours are you working on public holidays?";
        float hours = get_hours(prompt);
};


