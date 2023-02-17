#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

typedef unsigned int uint;

std::ifstream DatabaseHandler;

// Оценка расходов студента, руб./ месяц на основе "статистических данных"

/*bool initDatabase() {
    // Инициализация базы данных
    return;
}
*/

uint getOtherMontlyCosts(uint month, const std::string& city,
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
        return 0;
    } 
    while (1) {
        if(fd.eof()) {
            return 0;
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
        return 0;
    }
    uint res = std::stoi(food);
    return res;

}

uint getHomeFoodCost(const std::string& city) {
    // Получаем из базы данных средние по региону затраты на еду
    // что такое средние по региону
    std::fstream fd;
    std::string str;
    std::string food;
    std::string CurCity;
    std::stringstream strStream(str);
    fd.open("Costs.csv",std::fstream::in);
    if (!(fd.is_open())){
        return 0;
    } 
    while (1) {
        if(fd.eof()) {
            return 0;
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

uint getCinemaCost(const std::string& city, const std::string& cinema) {
    // Получаем из базы данных стоимость билета на вечерний сеанс в данном кинотетре
    std::fstream fd;
    std::string str;
    std::string CurCity;
    std::string cost;
    std::string CurCinema;
    std::stringstream strStream(str);
    fd.open("Caffe-and-cinema.csv",std::fstream::in);
    if (!(fd.is_open())) {
        return 0;
    } 
    while (1) {
        if(fd.eof()) {
            return 0;
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

uint getCoffeeCost(const std::string& city, const std::string& coffee) {
    // Получаем из базы данных средний чек в данном баре
    std::fstream fd;
    std::string str;
    std::string CurCity;
    std::string cost;
    std::string CurCaffe;
    std::stringstream strStream(str);
    fd.open("Caffe-and-cinema.csv",std::fstream::in);
    if (!(fd.is_open())) {
        return 0;
    } 
    while (1) {
        if(fd.eof()) {
            return 0;
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
    return res;
}

uint getWeekandCost(const std::string& city, const std::string& cinema,
                    const std::string& coffee) {
    /* По выходным дням расходы складываются из стоимости:
     - похода в кино (пешком)
     - похода  в кафе (пешком)
     - завтрака и обеда дома */

    return static_cast<uint>(0.66 * getHomeFoodCost(city) + 
        getCinemaCost(city, cinema) + getCoffeeCost(city, coffee) + 0.5);
}

uint getInstituteDinnerCost(const std::string& city, const std::string& institute) {
    // Получаем из базы данных среднюю стоимость обеда в столовой данного института
    std::fstream fd;
    std::string str;
    std::string CurCity;
    std::string cost;
    std::string CurInstitute;
    std::stringstream strStream(str);
    fd.open("Institute.csv",std::fstream::in);
    if (!(fd.is_open())) {
        return 0;
    } 
    while (1) {
        if(fd.eof()) {
            return 0;
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

uint getTransportCost(const std::string& city, const std::string& homeAddress,
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
        return 0;
    } 
    while (1) {
        if(fd.eof()) {
            return 0;
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

uint getWorkdayCost(const std::string& city, const std::string& homeAddress,
                    const std::string& institute) {
   /* По рабочим дням расходы складываются из стоимости:
    - дороги до института и обратно 
    - обеда в институтской столовой
    - завтрака и обеда дома */

    return static_cast<uint>(2 * getTransportCost(city, homeAddress, institute) +
        getInstituteDinnerCost(city, institute) + 0.66 * getHomeFoodCost(city) + 0.5);
}

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

uint getCosts(uint month, const std::string& city, const std::string& homeAddress, 
              const std::string& institute, const std::string& cinema,
              const std::string& coffee, uint age) {
    /* Расходы:
     - по рабочим дням
     - по выходным дням
     - прочие расходы */

    const uint daysCount = getDaysCount(month);
    const uint workDays = getWorkdays(month);
    const uint weekends = daysCount - workDays;

    return workDays * getWorkdayCost(city, homeAddress, institute) +
           weekends * getWeekandCost(city, cinema, coffee) + 
           getOtherMontlyCosts(month, city, age);
}

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
    const uint month = getMonth();
    const uint age = getAge();
    const std::string city = getCity();
    const std::string homeAddress = getAddress(city);
    const std::string institute = getInstitute(city);
    const std::string coffee = getCoffee(city);
    const std::string cinema = getCinema(city);

    const uint montlyCosts = getCosts(month, city, homeAddress, institute, 
        cinema, coffee, age);

    std::cout << "Expenses in a this month: " << montlyCosts << std::endl;

    //std::cout << getWorkdayCost("Moscow","Novokosino", "MIREA") << std::endl;
    return 0;
}
