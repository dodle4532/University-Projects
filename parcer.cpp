#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <algorithm>

class People {
public:
    People() = default;
    People(std::size_t _id, std::string _surName, std::string _name, int _age, unsigned int _phoneNumber) :
    id(_id), surname(_surName), name(_name), phoneNumber(_phoneNumber), age(_age) {}

    friend std::ofstream& operator<<(std::ofstream& out, People people) {
        if (people.id == 0) {
            return out;
        }
        out << people.id << " " << people.surname << " " << people.name << " " << people.age << " " << people.phoneNumber; 
        return out;
    }

    friend std::ostream& operator<<(std::ostream& out, People people) {
        if (people.id == 0) {
            return out;
        }
        out << people.id << " " << people.surname << " " << people.name << " " << people.age << " " << people.phoneNumber; 
        return out;
    }

    std::size_t getId() const {
        return id;
    }

    std::string getSurname() const {
        return surname;
    }

    std::string getName() const {
        return name;
    }

    unsigned int getPhoneNumber() const {
        return phoneNumber;
    }

    int getAge() const {
        return age;
    }

    bool isNull() const {
        if (id == 0) {
            return true;
        }
        return false;
    }

private:
    std::string surname;
    std::string name;
    unsigned int phoneNumber;
    int age;
    std::size_t id;
};


class DataBase {
public:
    DataBase(std::string _filePath) {
        maxId = 0;
        filePath = _filePath;
        std::fstream fd;
        fd.open(filePath);
        if (!(fd.is_open())) {
            throw std::out_of_range ("COULDN'T OPEN FILE");
        }
        load(fd);
        fd.close();
    }

    DataBase(std::string* _filePath) {
        maxId = 0;
        filePath = *_filePath;
        std::transform(filePath.begin(), filePath.end(), filePath.begin(), ::tolower);
        std::fstream fd;
        fd.open(filePath);
        if (fd.is_open()) {
            throw std::out_of_range ("THIS FILE IS ALREADY EXISTS");
        }
        fd.close();
        std::ofstream f (filePath);
        f.close();
        fd.open(filePath);
        if (!(fd.is_open())) {
            throw std::out_of_range ("COULDN'T OPEN FILE");
        }
        load(fd);
        fd.close();
    }

    void save() {
        std::ofstream fd(filePath, std::ofstream::trunc);
        for (int i = 0; i < table.size() - 1; ++i) {
            fd << table[i] << std::endl;
        }
        fd << table[table.size() - 1];
    }

    void load(std::fstream& fd) {
        std::string str;
        std::stringstream ss;
        std::string curSurname;
        std::string curName;
        std::string curPhoneNumber;
        std::string curAge;
        std::string curId;
        unsigned int phoneNumber;
        int age;
        while (!(fd.eof())) {
            std::getline(fd, str);
            if (str == "") {
                continue;
            }
            ss.clear();
            ss.str(str);
            while (!(ss.eof())) {
                std::getline(ss, curId, ' ');
                std::size_t id = std::stoi(curId);
                std::getline(ss, curSurname, ' ');
                std::getline(ss, curName, ' ');
                std::getline(ss, curAge, ' ');
                std::getline(ss, curPhoneNumber, ' ');
                try {
                    phoneNumber =  std::stoi(curPhoneNumber);
                    age = std::stoi(curAge);
                }
                catch(std::invalid_argument e) {
                    table.clear();
                    throw std::out_of_range ("INCORRECT DATABASE");
                }
                People people(id, curSurname, curName, age, phoneNumber);
                add(people);
            }
            if (table.size() == 0) {
                continue;
            }
        }
    }

    bool add(People people) {
        int id = people.getId() - 1;
        if (id > maxId - 1) {
            for (int i = maxId - 1; i < id; ++i) {
                table.push_back(People(0, "", "", 0, 0));
            }
            maxId = id + 1;
        }
        if (!(table[id].isNull())) {
            return false;
        }
        table[id] = people;
        return true;
    }

    People& get(std::size_t id) {
        return table[id - 1];
    }

    int size() {
        return table.size();
    }

    bool del(std::size_t id) {
        if (id < 1 || id > size()) {
            return false;
        }
        if (id == size()) {
            table.pop_back();
            return true;
        }
        table[id - 1] = People(0, "", "", 0, 0);
        return true;
    }

    bool isEmpty(std::size_t id) {
        if (id > size() || id < 0) {
            return true;
        }
        if (table[id - 1].isNull()) {
            return true;
        }
        return false;
    }

    void change(std::size_t id, People people) {
        if (id != people.getId()) {
            del(id);
            add(people);
            return;
        }
        table[id - 1] = people;
    }

private:
    std::vector <People> table;
    int maxId = 0;
    std::string filePath;
};


int main() {
    DataBase* dataBase = nullptr;
    std::string str;
    unsigned char keyBoard;
    while (1) {
        std::cout << "ENTER COMMAND:" << std::endl;
        while (keyBoard != 13) {
            keyBoard = _getch();
            if (keyBoard == 13) {
                break;
            }
            str += keyBoard;
            std::transform(str.begin(), str.end(), str.begin(), ::toupper);
            system("cls");
            if (keyBoard == 8 && str != "") {
                str.erase(str.end() - 2);
                str.resize(str.size() - 1);
            }
            std::cout << "ENTER COMMAND:" << std::endl;
            std::cout << str;
        }
        keyBoard = 0;
        system("cls");
        std::stringstream ss;
        std::string command;
        std::string argument;
        ss.clear();
        ss.str(str);
        std::getline(ss, command, ' ');
        std::getline(ss, argument, ' ');
        if (command == "ADD") {
            if (dataBase == nullptr) {
                std::cout << "DATABASE ISN'T OPEN" << std::endl;
                str.clear();
                continue;
            }
            std::size_t id;
            std::string curSurname;
            std::string curName;
            int age;
            unsigned int curPhoneNumber;
            while (1) {
                std::cout << "ENTER DATA(ID, SURNAME, NAME, AGE, PHONENUMBER)" << std::endl;
                std::cin >> id >> curSurname >> curName >> age >> curPhoneNumber;
                if (!(dataBase->add(People(id, curSurname, curName, age, curPhoneNumber)))) {
                    std::cout << "THIS ID IS ALREADY FILLED" << std::endl;
                    continue;
                }
                break;
            }   
            std::cout << "ADD SUCCESSFUL" << std::endl;
            str.clear();
            dataBase->save();
            continue;
        }

        if (command == "GET") {
            if (dataBase == nullptr) {
                std::cout << "DATABASE ISN'T OPEN" << std::endl;
                str.clear();
                continue;
            }

            std::size_t id = std::stoi(argument);
            if (id > dataBase->size() || id < 1) {
                std::cout << "WROND ID" << std::endl;
                str.clear();
                continue;
            }
            People p = dataBase->get(id);
            std::cout << p << std::endl;
            str.clear();
            continue;
        }

        if (command == "CHANGE") {
            if (dataBase == nullptr) {
                std::cout << "DATABASE ISN'T OPEN" << std::endl;
                str.clear();
                continue;
            }
            std::size_t id = std::stoi(argument);
            if (id > dataBase->size() || id < 1) {
                std::cout << "WROND ID" << std::endl;
                str.clear();
                continue;
            }

            People people = dataBase->get(id);
            std::size_t newId = people.getId();
            std::string surname = people.getSurname();
            std::string name = people.getName();
            int age = people.getAge();
            unsigned int phone = people.getPhoneNumber();

            int elem;
            std::string value;

            system("cls");

            while (1) {
                std::cout << "ENTER DATA NUMBER(1 - ID, 2 - SURNAME 3 - NAME, 4 - AGE, 5 - PHONENUMBER)" << std::endl;
                std::cout << "AND NEW VALUE" << std::endl;
                std::cin >> elem >> value;
                if (elem < 0 || elem > 5) {
                    std::cout << "WRONG DATA NUMBER" << std::endl;
                    continue;
                }
                if (elem == 1) {
                    newId = std::stoi(value);
                    if (newId < 0 || newId > dataBase->size() || dataBase->isEmpty(newId) == false) {
                        std::cout << "WRONG ID" << std::endl;
                        continue;
                    }
                }
                std::cin.clear();
                break;
            }

            switch (elem)
            {
            case 2:
                surname = value;
                break;
            case 3:
                name = value;
                break;
            case 4:
                age = std::stoi(value);
                break;
            case 5:
                phone = std::stoi(value);
                break;
            }
            people = People(newId, surname, name, age, phone);
            dataBase->change(id, people);
            std::cout << "CHANGE SUCCESSFUL" << std::endl;
            str.clear();
            dataBase->save();
            continue;

        }

        if (command == "DELETE") {
            if (dataBase == nullptr) {
                std::cout << "DATABASE ISN'T OPEN" << std::endl;
                str.clear();
                continue;
            }
            std::size_t id = std::stoi(argument);
            if (!(dataBase->del(id))) {
                std::cout << "WROND ID" << std::endl;
                str.clear();
                continue;
            }
            std::cout << "DELETE SUCCESSFUL" << std::endl;
            dataBase->save();
            str.clear();
            continue;

        }

        if (command == "LOAD") {
            try {
                dataBase = new DataBase(argument);
            }
            catch(std::out_of_range e) {
                std::cout << e.what() << std::endl;
                str.clear();
                continue;
            }
            str.clear();
            std::cout << "LOAD SUCCESSFUL" << std::endl;
            continue;
        }

        if (command == "NEW") {
            try {
                dataBase = new DataBase(&argument);
            }
            catch(std::out_of_range e) {
                std::cout << e.what() << std::endl;
                str.clear();
                continue;
            }
            str.clear();
            std::cout << "CREATING SUCCESSFUL" << std::endl;
            continue;
        }

        if (command == "SAVE") {
            dataBase->save();
            continue;
        }
        if (command == "Q") {
            std::exit(0);
        }

        std::cout << "WROND COMMAND" << std::endl;
        str.clear();
    }
}