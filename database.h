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
        uint getOtherMontlyCosts(const uint month, const std::string& city,
                                 const uint age);
        uint getHomeFoodCost(const std::string& city);
        uint getCinemaCost(const std::string& city, const std::string& cinema);
        uint getCoffeCost(const std::string& city, const std::string& coffe);
        uint getWeekandCost(const std::string& city, const std::string& institute);
        uint getInstituteDinnerCost(const std::string& city, const std::string& institute);
        uint getTransportCost(const std::string& city, const std::string& homeAddress,
                              const std::string& institute);
        
};