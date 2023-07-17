#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <functional>

using namespace std;

class AppUI;

typedef function<void(AppUI&)> command;

// Самостоятельное задание:
//    создать команды '+', '-', '*', '/'

// Управляющий класс программы
class AppUI {
    map<string,command> functions;
public:
    void add(string name, command cmd) {
        functions[name] = cmd;
    }

    void printGuide() {
        cout << "'+' - сложить два числа" << endl;
        cout << "'-' - вычесть b из a" << endl;
        cout << "'*' - умножить a на b" << endl;
        cout << "'/' - разделить a на b" << endl;
    }

    double readNumber() {
        cout << "Введите число: ";
        double x;
        cin >> x;
        cin.ignore(1, '\n');
        return x;
    }

    void cls() {
        system("cls");
    }

    void answer(double value) {
        cout << "Ответ: " << value << endl;
        pause();
    }

    void pause() {
        cout << "Нажмите Enter чтобы продолжить..";
        string s;
        getline(cin, s);
    }

    void mainloop() {
        while (cin.good()) {
            cls();
            printGuide();
            string cmd;
            cout << "> ";
            getline(cin, cmd);
            if (cmd == "exit") {
                break;
            }
            auto found = functions.find(cmd);
            if (found == functions.end()) {
                cerr << "Команда не найдена " << endl;
                pause();
                continue;
            }
            command func = found->second;
            func(*this);
        }
    }
};

int main(){
    setlocale(LC_ALL, "");
    ifstream file("Text.txt");

    AppUI app;
    app.add("+", [](AppUI& ui) {
        double a = ui.readNumber();
        double b = ui.readNumber();
        ui.answer(a + b);
    });

    app.add("/", [](AppUI& ui) {
        double a = ui.readNumber();
        double b = ui.readNumber();
        if (b == 0.0) {
            cerr << "деление на ноль!" << endl;
        }
        else {
            cout << a / b << endl;
        }
        ui.pause();
    });
    app.mainloop();
    return 0;
}