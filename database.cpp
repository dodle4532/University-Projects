#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "student.h"
#include "database.h"

typedef unsigned int uint;

const std::string DatabaseHandler::costsFileName = "Costs.csv";
const std::string DatabaseHandler::caffeAndCinemaFileName = "Caffe-and-cinema.csv";
const std::string DatabaseHandler::instituteFileName = "Institute.csv";
const std::string DatabaseHandler::transportFileName = "Transport.csv";

uint DatabaseHandler::getOtherMontlyCosts(const uint month, const std::string& city,
                                 const uint age)
{
    /* Получаем из базы данных средние по региону затраты в данном месяце 
     для людей данного возраста
    (по остальным статьям кроме еды, транспорта и развлечений) */
    std::fstream fd;
    std::string str;
    std::string food;
    std::string CurAge;
    std::string CurCity;
    std::stringstream ss;
    ss << age;
    std::string strAge = ss.str();
    std::stringstream strStream;
    fd.open(costsFileName, std::fstream::in);
    if (!(fd.is_open())) {
        std::cout << "ERROR" << std::endl;
        std::exit(0);
    } 
    while (1) {
        if(fd.eof()) {
            std::cout << "Not found otherMothlyCost in DATABASE" << std::endl;
            std::exit(0);
        }
        std::getline(fd, str);
        strStream.clear();
        strStream.str(str);
        std::getline(strStream, CurCity, ',');
        if (CurCity == city) {
            std::getline(strStream, CurAge, ',');
            if(CurAge == strAge) {
                std::getline(strStream, food, ',');
                std::getline(strStream, food, ',');
                break;
            }
            
        }
    }
    if (food == "") {
        return -1;
    }
    uint res = std::stoi(food);
    return res;

}

uint DatabaseHandler::getHomeFoodCost(const std::string& city) {
    // Получаем из базы данных средние по региону затраты на еду
    // что такое средние по региону
    std::fstream fd;
    std::string str;
    std::string food;
    std::string CurCity;
    std::stringstream strStream(str);
    fd.open(costsFileName,std::fstream::in);
    if (!(fd.is_open())){
        std::cout << "ERROR" << std::endl;
        std::exit(0);
    } 
    while (1) {
        if(fd.eof()) {
            std::cout << "Not found homeFoodCost in DATABASE" << std::endl;
            std::exit(0);
        }
        std::getline(fd, str);
        strStream.clear();
        strStream.str(str);
        std::getline(strStream, CurCity, ',');
        if (CurCity == city) {
            std::getline(strStream, food, ',');
            std::getline(strStream, food, ',');
            break;
        }
    }
    uint res = std::stoi(food) / 30;
    return res;
}

uint DatabaseHandler::getCinemaCost(const std::string& city, const std::string& cinema) {
    // Получаем из базы данных стоимость билета на вечерний сеанс в данном кинотетре
    std::fstream fd;
    std::string str;
    std::string CurCity;
    std::string cost;
    std::string CurCinema;
    std::stringstream strStream(str);
    fd.open(caffeAndCinemaFileName,std::fstream::in);
    if (!(fd.is_open())) {
        std::cout << "ERROR" << std::endl;
        std::exit(0);
    } 
    while (1) {
        if(fd.eof()) {
            std::cout << "Not found cinemaCost in DATABASE" << std::endl;
            std::exit(0);
        }
        std::getline(fd, str);
        
        strStream.clear();
        strStream.str(str);
        std::getline(strStream, CurCity, ',');
        if (CurCity == city) {
            std::getline(strStream, CurCinema, ',');
            std::getline(strStream, CurCinema, ',');
            std::getline(strStream, CurCinema, ',');
            std::getline(strStream, CurCinema, ',');
            if (CurCinema == cinema) {
                std::getline(strStream, cost, ',');
                break;
            }
        }
    }
    uint res = std::stoi(cost);
    return res;
}

uint DatabaseHandler::getCoffeCost(const std::string& city, const std::string& coffe) {
    // Получаем из базы данных средний чек в данном баре
    std::fstream fd;
    std::string str;
    std::string CurCity;
    std::string cost;
    std::string CurCaffe;
    std::stringstream strStream(str);
    fd.open(caffeAndCinemaFileName,std::fstream::in);
    if (!(fd.is_open())) {
        std::cout << "ERROR" << std::endl;
        std::exit(0);
    } 
    while (1) {
        if(fd.eof()) {
            std::cout << "Not found coffeCost in DATABASE" << std::endl;
            std::exit(0);
        }
        std::getline(fd, str);
        strStream.clear();
        strStream.str(str);
        std::getline(strStream, CurCity, ',');
        if (CurCity == city) {
            std::getline(strStream, CurCaffe, ',');
            std::getline(strStream, CurCaffe, ',');
            if (CurCaffe == coffe) {
                std::getline(strStream, cost, ',');
                break;
            }
        }
    }
    uint res = std::stoi(cost);
    return res;
}

uint DatabaseHandler::getInstituteDinnerCost(const std::string& city, const std::string& institute) {
    // Получаем из базы данных среднюю стоимость обеда в столовой данного института
    std::fstream fd;
    std::string str;
    std::string CurCity;
    std::string cost;
    std::string CurInstitute;
    std::stringstream strStream(str);
    fd.open(instituteFileName,std::fstream::in);
    if (!(fd.is_open())) {
        std::cout << "ERROR" << std::endl;
        std::exit(0);
    } 
    while (1) {
        if(fd.eof()) {
            std::cout << "Not found instituteDinnerCost in DATABASE" << std::endl;
            std::exit(0);
        }
        std::getline(fd, str);
        strStream.clear();
        strStream.str(str);
        std::getline(strStream, CurCity, ',');
        if (CurCity == city) {
            std::getline(strStream, CurInstitute, ',');
            if (CurInstitute == institute) {
                std::getline(strStream, cost, ',');
                break;
            }
        }
    }
    uint res = std::stoi(cost);
    return res;
}

uint DatabaseHandler::getTransportCost(const std::string& city, const std::string& homeAddress,
                                       const std::string& institute) {
    // Получаем из базы данных стоимость кратчайшей дороги до инстиутта
    std::fstream fd;
    std::string str;
    std::string CurCity;
    std::string cost;
    std::string CurInstitute;
    std::string CurHomeAddress;
    std::stringstream strStream(str);
    fd.open(transportFileName,std::fstream::in);
    if (!(fd.is_open())) {
        std::cout << "ERROR" << std::endl;
        std::exit(0);
    } 
    while (1) {
        if(fd.eof()) {
            std::cout << "Not found transportCost in DATABASE" << std::endl;
            std::exit(0);
        }
        std::getline(fd, str);
        strStream.clear();
        strStream.str(str);
        std::getline(strStream, CurCity, ',');
        if (CurCity == city) {
            std::getline(strStream, CurHomeAddress, ',');
            if (CurHomeAddress == homeAddress) {
                std::getline(strStream, CurInstitute, ',');
                if (CurInstitute == institute) {
                    std::getline(strStream, cost, ',');
                    break;
                }
            }
        }
    }
    uint res = std::stoi(cost);
    return res;
}



