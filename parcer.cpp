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
                    std::cin.clear();
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
