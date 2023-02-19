#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "class.h"

typedef unsigned int uint;

uint getWorkdays(uint month) {
   // Получаем число рабочих дней данном в месяце
    if (month == 1 && month == 3 && month == 5 && month == 7
        && month == 8 && month == 10) {
            return 20;
    }
     else if (month == 4 && month == 3 && month == 6 && month == 9
        && month == 11) {
        return 19;
    }
    else {
        return 17;
    }
}

uint getDaysCount(uint month) {
    // Вычисляем количество дней в месяце
    if (month == 1 && month == 3 && month == 5 && month == 7
        && month == 8 && month == 10) {
            return 31;
    }
    else if (month == 4 && month == 3 && month == 6 && month == 9
        && month == 11) {
            return 30;
    }
    else {
        return 28;
    }
}



void DatabaseHandler::setOtherMontlyCosts(uint month, const std::string& city,
    uint age)
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
    fd.open("Costs.csv",std::fstream::in);
    if (!(fd.is_open())){
        DatabaseHandler::otherMontlyCosts = 0;
        return;
    } 
    while (1) {
        if(fd.eof()) {
            DatabaseHandler::otherMontlyCosts = 0;
            return;
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
        DatabaseHandler::otherMontlyCosts = 0;
        return;
    }
    uint res = std::stoi(food);
    DatabaseHandler::otherMontlyCosts = res;
    return;

}

void DatabaseHandler::setHomeFoodCost(const std::string& city) {
    // Получаем из базы данных средние по региону затраты на еду
    // что такое средние по региону
    std::fstream fd;
    std::string str;
    std::string food;
    std::string CurCity;
    std::stringstream strStream(str);
    fd.open("Costs.csv",std::fstream::in);
    if (!(fd.is_open())){
        DatabaseHandler::homeFoodCost = 0;
        return;
    } 
    while (1) {
        if(fd.eof()) {
            DatabaseHandler::homeFoodCost = 0;
            return;
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
    DatabaseHandler::homeFoodCost = res;
    return;
}

void DatabaseHandler::setCinemaCost(const std::string& city, const std::string& cinema) {
    // Получаем из базы данных стоимость билета на вечерний сеанс в данном кинотетре
    std::fstream fd;
    std::string str;
    std::string CurCity;
    std::string cost;
    std::string CurCinema;
    std::stringstream strStream(str);
    fd.open("Caffe-and-cinema.csv",std::fstream::in);
    if (!(fd.is_open())) {
        DatabaseHandler::cinemaCost = 0;
        return;
    } 
    while (1) {
        if(fd.eof()) {
            DatabaseHandler::cinemaCost = 0;
            return;
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
    DatabaseHandler::cinemaCost = res;
    return;
}

void DatabaseHandler::setCoffeeCost(const std::string& city, const std::string& coffee) {
    // Получаем из базы данных средний чек в данном баре
    std::fstream fd;
    std::string str;
    std::string CurCity;
    std::string cost;
    std::string CurCaffe;
    std::stringstream strStream(str);
    fd.open("Caffe-and-cinema.csv",std::fstream::in);
    if (!(fd.is_open())) {
        DatabaseHandler::coffeeCost = 0;
        return;
    } 
    while (1) {
        if(fd.eof()) {
            DatabaseHandler::coffeeCost = 0;
            return;
        }
        std::getline(fd, str);
        strStream.clear();
        strStream.str(str);
        std::getline(strStream, CurCity, ',');
        if (CurCity == city) {
            std::getline(strStream, CurCaffe, ',');
            std::getline(strStream, CurCaffe, ',');
            if (CurCaffe == coffee) {
                std::getline(strStream, cost, ',');
                break;
            }
        }
    }
    uint res = std::stoi(cost);
    DatabaseHandler::coffeeCost = res;
    return;
}

void DatabaseHandler::setInstituteDinnerCost(const std::string& city, const std::string& institute) {
    // Получаем из базы данных среднюю стоимость обеда в столовой данного института
    std::fstream fd;
    std::string str;
    std::string CurCity;
    std::string cost;
    std::string CurInstitute;
    std::stringstream strStream(str);
    fd.open("Institute.csv",std::fstream::in);
    if (!(fd.is_open())) {
        DatabaseHandler::instituteDinnerCost = 0;
        return;
    } 
    while (1) {
        if(fd.eof()) {
            DatabaseHandler::instituteDinnerCost = 0;
            return;
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
    DatabaseHandler::instituteDinnerCost = res;
    return;
}

void DatabaseHandler::setTransportCost(const std::string& city, const std::string& homeAddress,
                                       const std::string& institute) {
    // Получаем из базы данных стоимость кратчайшей дороги до инстиутта
    std::fstream fd;
    std::string str;
    std::string CurCity;
    std::string cost;
    std::string CurInstitute;
    std::string CurHomeAddress;
    std::stringstream strStream(str);
    fd.open("Transport.csv",std::fstream::in);
    if (!(fd.is_open())) {
        DatabaseHandler::transportCost = 0;
        return;
    } 
    while (1) {
        if(fd.eof()) {
            DatabaseHandler::transportCost = 0;
            return;
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
    DatabaseHandler::transportCost = res;
    return;
}

uint DatabaseHandler::getOtherMontlyCosts() {
    return otherMontlyCosts;
}
uint DatabaseHandler::getHomeFoodCost() {
    return homeFoodCost;
}
uint DatabaseHandler::getCinemaCost() {
    return cinemaCost;
}
uint DatabaseHandler::getCoffeeCost() {
    return coffeeCost;
}

uint DatabaseHandler::getInstituteDinnerCost() {
    return instituteDinnerCost;
}
uint DatabaseHandler::getTransportCost() {
    return transportCost;
}



Student::Student(uint age, uint workdayCost, uint weekandCost, uint cost,
                std::string city, std::string homeAddress, std::string institute,
                std::string coffee, std::string cinema) {
    this->age = age;
    this->workdayCost = workdayCost;
    this->weekandCost = weekandCost;
    this->cost = cost;
    this->city = city;
    this->homeAddress = homeAddress;
    this->institute = institute;
    this->coffee = coffee;
    this->cinema = cinema;
}
        
Student::Student() {
    age = 0;
    workdayCost = 0;
    weekandCost = 0;
    cost = 0;
    city = "";
    homeAddress = "";
    institute = "";
    coffee = "";
    cinema = "";
}

void Student::setWorkdayCost(DatabaseHandler &a) {
   /* По рабочим дням расходы складываются из стоимости:
    - дороги до института и обратно 
    - обеда в институтской столовой
    - завтрака и обеда дома */

    Student::workdayCost = static_cast<uint>(2 * a.getTransportCost() +
        a.getInstituteDinnerCost() + 0.66 * a.getHomeFoodCost() + 0.5);
}

void Student::setWeekandCost(DatabaseHandler &a) {
    /* По выходным дням расходы складываются из стоимости:
     - похода в кино (пешком)
     - похода  в кафе (пешком)
     - завтрака и обеда дома */

    Student::weekandCost = static_cast<uint>(0.66 * a.getHomeFoodCost() + 
                                             a.getCinemaCost() + 
                                             a.getCoffeeCost() + 0.5);
}

void Student::setCost(uint month, DatabaseHandler a) {
    /* Расходы:
     - по рабочим дням
     - по выходным дням
     - прочие расходы */

    const uint daysCount = getDaysCount(month);
    const uint workDays = getWorkdays(month);
    const uint weekends = daysCount - workDays;

    Student::cost = workDays * Student::getWorkdayCost() +
           weekends * Student::getWeekandCost() + 
           a.getOtherMontlyCosts();
}

uint Student::getWorkdayCost() {
    return workdayCost;
}

uint Student::getWeekandCost() {
    return weekandCost;
}

uint Student::getCost() {
    return cost;
}

void Student::setAge(const int age) {
    this->age = age;
}

void Student::setCity(const std::string& city) {
    this->city = city;
}

void Student::setHomeAdress(const std::string& homeAdress) {
    this->homeAddress = homeAdress;
}

void Student::setInstitute(const std::string& institute) {
    this->institute = institute;
}

void Student::setCoffee(const std::string& coffee) {
    this->coffee = coffee;
}

void Student::setCinema(const std::string& cinema) {
    this->cinema = cinema;
}   

uint Student::getAge() {
    return age;
}

std::string Student::getCity() {
    return city;
}

std::string Student::getHomeAdress() {
    return homeAddress;
}

std::string Student::getInstitute() {
    return institute;
}

std::string Student::getCoffee() {
    return coffee;
}

std::string Student::getCinema() {
    return cinema;
}
