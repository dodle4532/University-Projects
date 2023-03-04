#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

typedef unsigned int uint;

class Student {
    private:
        std::string _name;
        uint _age;
        // uint workdayCost;
        // uint weekandCost;
        // uint cost;
        std::string _city;
        std::string _homeAddress;
        std::string _institute;
        // std::string coffee;
        // std::string cinema;


    public:
        Student(const std::string& name, const uint age, const std::string& city, const std::string& homeAddress,
                 const std::string& institute);
        Student();

        // void setWorkdayCost(DatabaseHandler &a);
        // void setWeekandCost(DatabaseHandler &a);
        // void setCost(uint month, DatabaseHandler a);

        uint getWorkdayCost(const uint TransportCost, const uint InstituteDinnerCost, 
                            const uint HomeFoodCost);
        uint getWeekandCost(const uint HomeFoodCost, const uint CinemaCost, 
                            const uint CoffeeCost);
        uint getMonthlyCost(const uint month, const uint WorkdayCost, const uint WeekandCost,
                     const uint OtherMontlyCosts);       
        std::string getCoffe();
        std::string getCinema();
        
        void setName(const std::string& name);
        void setAge(const uint age);
        void setCity(const std::string& city);
        void setHomeAdress(const std::string& homeAdress);
        void setInstitute(const std::string& institute);
        // void setCoffee(const std::string& coffee);
        // void setCinema(const std::string& cinema);

        // void setCinema();
        // void setCoffee();
        void setInstitute();
        void setHomeAdress();
        void setAge();
        void setCity();
        void setName();

        std::string getName();
        uint getAge();
        std::string getCity();
        std::string getHomeAdress();
        std::string getInstitute();

};