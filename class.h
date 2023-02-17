#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

typedef unsigned int uint;

class DatabaseHandler {
    private:
        uint otherMontlyCosts;
        uint homeFoodCost;
        uint cinemaCost;
        uint coffeeCost;
        uint instituteDinnerCost;
        uint transportCost;

    public:
        void setOtherMontlyCosts(uint month, const std::string& city,
                                 uint age);
        void setHomeFoodCost(const std::string& city);
        void setCinemaCost(const std::string& city, const std::string& cinema);
        void setCoffeeCost(const std::string& city, const std::string& coffee);
        void setInstituteDinnerCost(const std::string& city, const std::string& institute);
        void setTransportCost(const std::string& city, const std::string& homeAddress,
                              const std::string& institute);

        uint getOtherMontlyCosts();
        uint getHomeFoodCost();
        uint getCinemaCost();
        uint getCoffeeCost();
        uint getWeekandCost();
        uint getInstituteDinnerCost();
        uint getTransportCost();
        
};

class Student {
    private:
        uint age;
        uint workdayCost;
        uint weekandCost;
        uint cost;
        std::string city;
        std::string homeAddress;
        std::string institute;
        std::string coffee;
        std::string cinema;


    public:
        void setWorkdayCost(DatabaseHandler &a);
        void setWeekandCost(DatabaseHandler &a);
        void setCost(uint month, DatabaseHandler a);

        uint getWorkdayCost();
        uint getWeekandCost();
        uint getCost();
        
        void setAge(const int _age);
        void setCity(const std::string& _city);
        void setHomeAdress(const std::string& _homeAdress);
        void setInstitute(const std::string& _institute);
        void setCoffee(const std::string& _coffee);
        void setCinema(const std::string& _cinema);

        uint getAge();
        std::string getCity();
        std::string getHomeAdress();
        std::string getInstitute();
        std::string getCoffee();
        std::string getCinema();
};