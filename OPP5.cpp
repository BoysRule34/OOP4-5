// OPP5.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <vector>

using namespace std;


class Command {
public:
    virtual void execute() = 0;
};

class TalkCommand : public Command {
private:
    string phrase;
public:
    TalkCommand(string p_phrase) {
        phrase = p_phrase;
    }

    void changePhrase(string newPhrase) {
        phrase = newPhrase;
    }
    void execute() {
        cout << phrase << endl;
    }
};

class EatCommand : public Command {
private:
    string product = "грушу";
public:
    EatCommand() {

    }
    void execute() {
        cout << "*ест " + product + "*" << endl;
    }

    void changeProduct(string newProduct) {
        product = newProduct;
    }
};


class Bird {
private: 
    string name = "";
public:
    virtual void fly() = 0;
    virtual void tweet() = 0;
    virtual void doCommand(int number) = 0;
    virtual void doCommand(Command* command) = 0;
    virtual void teachCommand(Command* command) = 0;

    string getName() {
        return name;
    }

    void changeName(string newName) {
        name = newName;
    }

    void breathe() {
        cout << "*дышит*" << endl;
    }

};

class Pigeon : public Bird {
private:
    vector<Command*> mass;
    int length = 0;
public:

    Pigeon(string name) {
        changeName(name);
    }

    void fly() {
        cout << "летает" << endl; 
    }

    void tweet() {
        cout << "кур-лык" << endl;
    }

    void doCommand(int number) {
        if (length <= number) {
            cout << "птица не знает этой команды" << endl;
        } else {
            mass[number]->execute();
        }
    }

    void doCommand(Command* command) {
        if (command != nullptr)
            command->execute();
    }

    void teachCommand(Command* command) {
        mass.push_back(command);
        length++;
    }
};

class Aviary {
private: 
    int max = 10;
    int birdCounter = 0;
    vector<Bird*> mass;
public:
    int checkBirds() {
        return birdCounter;
    }

    Bird* getBird() {
        if (birdCounter == 0) {
            cout << "авиарий пуст!" << endl;
            return nullptr;
        } else {
            return mass[rand() % birdCounter];
        }
    }

    void throwIntoTheCage(Bird* bird) {
        mass.push_back(bird);
        birdCounter++;
    }

    void releaseBirds() {
        for (int i = 0; i < birdCounter; i++) {
            delete mass[i];
            birdCounter = 0;
        }
    }

    int getBirdCounter() {
        return birdCounter;
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");
    Aviary aviary = Aviary();
    int n;
    string name;
    string product;
    string phrase;
    EatCommand* eatCommand = new EatCommand();
    TalkCommand* talkCommand = new TalkCommand("кур-лык, кур-лык");
    Bird* bird = nullptr;
    Pigeon* pigeon = nullptr;
    while (true) {
        cout << "Добро пожаловать!" << endl;
        cout << "Что хотите сделать?" << endl;
        cout << "1 - создать голубя" << endl;
        cout << "2 - поместить голубя в авиарий" << endl;
        cout << "3 - взять голубя из авиария" << endl;
        cout << "любая другая - выйти" << endl;

        std::cin >> n;
        while (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        system ("cls");

        if (n == 1) {
            cout << "Как будут звать голубя?" << endl;
            std::cin >> name;
            while (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            pigeon = new Pigeon(name);
            cout << "голубь created" << endl;
        } else if (n == 2) {
            if (pigeon == nullptr)
                cout << "Для начала необходимо создать голубя!" << endl;
            else {
                cout << "вы точно хотите поместить голубя ";
                cout << pigeon->getName();
                cout << " в авиарий?  1 - yes, other - no" << endl;
                cin >> n;
                if (n == 1) 
                    aviary.throwIntoTheCage(pigeon);
                
            }
        } else if (n == 3 && aviary.getBirdCounter() != 0) {
            bird = aviary.getBird();
            cout << "Добро пожаловать в авиарий!" << endl;
            cout << "Вы взяли птицу - " + bird->getName() << endl;
            cout << "Что хотите сделать?" << endl;
            cout << "1 - накормить птицу" << endl;
            cout << "2 - научить птицу новой фразой" << endl;
            cout << "3 - послушать дыхание птицы" << endl;
            cout << "4 - выполнить команду" << endl;
            cout << "любая другая - выйти" << endl;

            cin >> n;
            while (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            if (n == 1) {
                cout << "что будет есть голубь?" << endl;
                cin >> product;
                eatCommand->changeProduct(product);
                bird->doCommand(eatCommand);
                cout << "запомнить команду? 1 - yes, other - no" << endl;
                cin >> n;
                if (n == 1)
                    bird->teachCommand(eatCommand);
            }
            else if (n == 2) {
                cout << "какой фразе обучить?" << endl;
                cin >> phrase;
                talkCommand->changePhrase(phrase);
                bird->doCommand(talkCommand);
                cout << "запомнить команду? 1 - yes, other - no" << endl;
                cin >> n;
                if (n == 1)
                    bird->teachCommand(eatCommand);
            }
            else if (n == 3)
                bird->breathe();
            else if (n == 4) {
                cout << "какую команду выполнить?" << endl;
                cin >> n;
                bird->doCommand(n);
            }
        }

    }
}

