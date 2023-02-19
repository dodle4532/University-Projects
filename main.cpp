#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "class.h"

typedef unsigned int uint;

std::string getCinema(const std::string& city) {
    // Аналогично getInstitute
    std::string cinema;
    std::cout << "What cinema is it?" << std::endl;
    std::cin >> cinema;
    return cinema;
}

std::string getCoffee(const std::string& city) {
    // Аналогично getInstitute
    std::string coffee;
    std::cout << "What coffee is it?" << std::endl;
    std::cin >> coffee;
    return coffee;
}

std::string getInstitute(const std::string& city) {
    // Ввод названия института
    std::string institute;
    std::cout << "What insitute is it?" << std::endl;
    std::cin >> institute;
    return institute;
}

std::string getAddress(const std::string& city) {
    // Запрашиваем ввод адреса
    std::string adress;
    std::cout << "What adress is it?" << std::endl;
    std::cin >> adress;
    return adress;
}

uint getAge() {
    // Запрашиваем ввод возраста
    uint age;
    std::cout << "What age is it?" << std::endl;
    std::cin >> age;
    return age;
}

std::string getCity() {
    // Запрашиваем ввод города
    std::string city;
    std::cout << "What city is it?" << std::endl;
    std::cin >> city;
    return city;
}

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
    const uint age = getAge();
    const std::string city = getCity();
    const std::string homeAddress = getAddress(city);
    const std::string institute = getInstitute(city);
    const std::string coffee = getCoffee(city);
    const std::string cinema = getCinema(city);
    student.setAge(age);
    student.setCinema(cinema);
    student.setCity(city);
    student.setCoffee(coffee);
    student.setHomeAdress(homeAddress);
    student.setInstitute(institute);
    
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