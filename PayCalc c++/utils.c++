namespace Utils
{

    std::string Convert_to_lowercase(std::string my_str) 
    {
        transform(my_str.begin(), my_str.end(), my_str.begin(), ::tolower);
        return my_str;
    
    }

    std::string yes_or_no()
    {
        std::string y_n;
        while(true)
        {
            std::cout << "[Y/N] >";
            std::cin >> y_n;
            y_n = Utils::Convert_to_lowercase(y_n);
            if(y_n == "y" || y_n == "n")
            {
                return y_n;
            }
            else
            {
                std::cout << "Please enter y or n!" << std::endl;
            }

        }
    }

    float misc_number()
    {
        float number;

        std::cout << " > ";
        while(true) 
        {
            if (std::cin >> number) 
            {
                return number;
            } else {
                    
                std::cout << "Please enter as a number!" << std::endl;
                std::cin.clear();
                while (std::cin.get() != '\n');
            }

        }       

    }

}
