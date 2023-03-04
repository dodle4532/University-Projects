#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

typedef unsigned int uint;

class DatabaseHandler {
    private:
        static const std::string costsFileName;
        static const std::string caffeAndCinemaFileName;
        static const std::string instituteFileName;
        static const std::string transportFileName;

    public:
        int getOtherMontlyCosts(const uint& month, const std::string& city,
                                 const uint& age);
        int getHomeFoodCost(const std::string& city);
        int getCinemaCost(const std::string& city, const std::string& cinema);
        int getCoffeCost(const std::string& city, const std::string& coffe);
        int getWeekandCost(const std::string& city, const std::string& institute);
        int getInstituteDinnerCost(const std::string& city, const std::string& institute);
        int getTransportCost(const std::string& city, const std::string& homeAddress,
                              const std::string& institute);
        
};