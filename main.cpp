#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "student.h"
#include "database.h"

typedef unsigned int uint;



bool isMonth(int month) {
    // Проверка: может ли введенное число интерпретироваться как месяц?
    if (month > 0 && month < 12) {
        return true;
    }
    return false;
}

uint getMonth() {
    // Запрашиваем ввод месяца для расчёта расходов 
    int month = 0;
    while (!isMonth(month))
    {
        std::cout << "What month is it?" << std::endl;
        std::cin >> month;
    }
    return month;
}


int main() {
    DatabaseHandler database;
    Student student;  
    const uint month = getMonth();

    student.setName("Igor");
    student.setAge();
    student.setCity();
    student.setHomeAdress();
    student.setInstitute();

    const uint age = student.getAge();
    const std::string city = student.getCity();
    const std::string homeAddress = student.getHomeAdress();
    const std::string institute = student.getInstitute();
    const std::string coffe = student.getCoffe();
    const std::string cinema = student.getCinema();
    const uint transportCost = database.getTransportCost(city, homeAddress, institute);
    const uint instituteDinnerCost = database.getInstituteDinnerCost(city, institute);
    const uint homeFoodCost = database.getHomeFoodCost(city);
    const uint cinemaCost = database.getCinemaCost(city, cinema);
    const uint coffeCost = database.getCoffeCost(city, coffe);
    const uint otherMonthlyCost = database.getOtherMontlyCosts(month, city, age);
    const uint workdayCost = student.getWorkdayCost(transportCost, instituteDinnerCost, homeFoodCost);
    const uint weekandCost = student.getWeekandCost(homeFoodCost, cinemaCost, coffeCost);

    // uint mothlyCost = student.getMonthlyCost(month, student.getWorkdayCost(database.getTransportCost(student.getCity(),student.getHomeAdress(), student.getInstitute()),
    //                            database.getInstituteDinnerCost(student.getCity(), student.getInstitute()), database.getHomeFoodCost(student.getCity())), 
    //                            student.getWeekandCost(database.getHomeFoodCost(student.getCity()), database.getCinemaCost(student.getCity(), student.getCinema()),
    //                            database.getCoffeCost(student.getCity(), student.getCoffe())), database.getOtherMontlyCosts(month, student.getCity(), student.getAge()));

    uint mothlyCost = student.getMonthlyCost(month, workdayCost, weekandCost, otherMonthlyCost);

    if (mothlyCost == 0) {
        std::cout << "WOW, " << student.getName() << " is living for FREE for entire month" << std::endl;
    }

    std::cout << "Expenses of " << student.getName() << " in a this month: " << mothlyCost << std::endl;

    return 0;  
}