#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "class.h"

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
    // const uint age = getAge();
    // const std::string city = getCity();
    // const std::string homeAddress = getAddress(city);
    // const std::string institute = getInstitute(city);
    // const std::string coffee = getCoffee(city);
    // const std::string cinema = getCinema(city);
    // student.setAge(age);
    // student.setCinema(cinema);
    // student.setCity(city);
    // student.setCoffee(coffee);
    // student.setHomeAdress(homeAddress);
    // student.setInstitute(institute);

    student.setAge();
    student.setCity();
    student.setHomeAdress();
    student.setInstitute();
    student.setCinema();
    student.setCoffee();
    
    database.setOtherMontlyCosts(month, student.getCity(), student.getAge());
    database.setHomeFoodCost(student.getCity());
    database.setCinemaCost(student.getCity(), student.getCinema());
    database.setCoffeeCost(student.getCity(), student.getCoffee());
    database.setInstituteDinnerCost(student.getCity(), student.getInstitute());
    database.setTransportCost(student.getCity(), student.getHomeAdress(), student.getInstitute());

    student.setWorkdayCost(database);
    student.setWeekandCost(database);

    student.setCost(month, database);

    uint res = student.getCost();

    if (res == 0) {
        std::cout << "WOW, student is living for FREE for entire month" << std::endl;
    }

    std::cout << "Expenses in a this month: " << res << std::endl;

    return 0;  
}