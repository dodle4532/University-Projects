#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "student.h"
#include "database.h"

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





Student::Student(const std::string& name, const uint age, const std::string& city, const std::string& homeAddress,
                 const std::string& institute) {
    _name = name;
    _age = age;
    _city = city;
    _homeAddress = homeAddress;
    _institute = institute;
}
        
Student::Student() {
    _age = 0;
}

uint Student::getWorkdayCost(const uint TransportCost, const uint InstituteDinnerCost, 
                             const uint HomeFoodCost) {
   /* По рабочим дням расходы складываются из стоимости:
    - дороги до института и обратно 
    - обеда в институтской столовой
    - завтрака и обеда дома */

    return static_cast<uint>(2 * TransportCost +
        InstituteDinnerCost + 0.66 * HomeFoodCost + 0.5);
}

uint Student::getWeekandCost(const uint HomeFoodCost, const uint CinemaCost, 
                             const uint CoffeeCost) {
    /* По выходным дням расходы складываются из стоимости:
     - похода в кино (пешком)
     - похода  в кафе (пешком)
     - завтрака и обеда дома */

    return static_cast<uint>(0.66 * HomeFoodCost + 
                             CinemaCost + 
                             CoffeeCost + 0.5);
}

uint Student::getMonthlyCost(const uint month, const uint WorkdayCost, const uint WeekandCost,
                      const uint OtherMontlyCosts) {
    /* Расходы:
     - по рабочим дням
     - по выходным дням
     - прочие расходы */

    const uint daysCount = getDaysCount(month);
    const uint workDays = getWorkdays(month);
    const uint weekends = daysCount - workDays;

    return workDays * WorkdayCost +
           weekends * WeekandCost + 
           OtherMontlyCosts;
}

void Student::setName(const std::string& name) {
    _name = name;
}
void Student::setAge(const uint age) {
    _age = age;
}

void Student::setCity(const std::string& city) {
    _city = city;
}

void Student::setHomeAdress(const std::string& homeAdress) {
    _homeAddress = homeAdress;
}

void Student::setInstitute(const std::string& institute) {
    _institute = institute;
}

   
std::string Student::getName() {
    return _name;
}
uint Student::getAge() {
    return _age;
}

std::string Student::getCity() {
    return _city;
}

std::string Student::getHomeAdress() {
    return _homeAddress;
}

std::string Student::getInstitute() {
    return _institute;
}

std::string Student::getCoffe() {

    std::string coffee;
    std::cout << "What coffee is it?" << std::endl;
    std::cin >> coffee;
    return coffee;
}

std::string Student::getCinema() {
    std::string cinema;
    std::cout << "What cinema is it?" << std::endl;
    std::cin >> cinema;
    return cinema;
}

void Student::setName() {
    std::string name;
    std::cout << "What is student name?" << std::endl;
    std::cin >> name;
    _name = name;
}
void Student::setInstitute() {
    // Ввод названия института
    std::string institute;
    std::cout << "What insitute is it?" << std::endl;
    std::cin >> institute;
    _institute = institute;
}

void Student::setHomeAdress() {
    // Запрашиваем ввод адреса
    std::string homeAdress;
    std::cout << "What adress is it?" << std::endl;
    std::cin >> homeAdress;
    _homeAddress = homeAdress;
}

void Student::setAge() {
    // Запрашиваем ввод возраста
    uint age;
    std::cout << "What age is it?" << std::endl;
    std::cin >> age;
    _age = age;
}

void Student::setCity() {
    // Запрашиваем ввод города
    std::string city;
    std::cout << "What city is it?" << std::endl;
    std::cin >> city;
    _city = city;
}