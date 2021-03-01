#include "people.h"
#include "graphics.h"
#include <cassert>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <QApplication>
#include <QWidget>

namespace wd {
    MainWindow main_window;
    StartWindow start_window(&main_window);
    LoginWindow login_window(&main_window);
    RegisterWindow register_window(&main_window);
    GeneralWindow general_window(&main_window);
}

//void general_window(people::Manager &manager);
void cilents_window(people::Manager &manager);
void enter_window();

/*void addClient_window(people::Manager &manager) {
    // open window
    std::string name, phone, email, deal_product;
    //    TODO think about skip after Qt
    //    TODO add exit button
    std::cout << "Input your email, skip: ~\n";
    std::cin >> email;
    std::cout << "Input your name, skip: ~\n";
    std::cin >> name;
    std::cout << "Input your phone, skip: ~\n";
    std::cin >> phone;
    std::cout << "Input your deal product, skip: ~\n";
    std::cin >> deal_product;
    manager.add_client({email, name, phone, deal_product});
    std::cout << "Ready? - 1\n";
    int number;
    std::cin >> number;
    assert(number == 1);
    cilents_window(manager);
    assert(false);
}*/

/*void manager_window(people::Manager &manager) {
    // open window
    std::cout << "Hello, ";
    std::cout << manager.get_name() << '\n';
    std::cout << "Your personal info: " << manager.get_info() << '\n';
    std::cout << "Here is a manager window. Here are some options:\n";
    std::cout << "1. Exit\n";
    int number;
    std::cin >> number;
    if (number == 1) { general_window(manager); }
    assert(false);
}

void deal_list_window(people::Manager &manager, int index) {
    // open window
    std::cout << "Here is a deal list window\n";
    std::cout << "Here is your deal status for: " << manager.list_clients[index].get_info() << '\n';
    std::vector<std::string> dealInfo = manager.list_clients[index].get_deal_process();
    for (const auto &s: dealInfo) {
        std::cout << s << '\n';
    }
    std::cout << "Here are some options:\n";
    std::cout << "1. Exit (button)\n";
    int number;
    std::cin >> number;
    assert(number == 1);
    cilents_window(manager);
    assert(false);
}

void cilents_window(people::Manager &manager) {
    // open window
    std::cout << "Here is a clients list:\n";
    int index = 1;
    for (const people::Client &client : manager.list_clients) {
        std::cout << index++ << ") " << client.get_info() << '\n';
    }
    std::cout << "Here is a clients window. Here are some options:\n";
    std::cout << "1. Change someone (I can realize it only with buttons)\n";
    std::cout << "2. Go to your deal list (button, not in the MVP) \n";
    std::cout << "3. Add someone (button)\n";
    std::cout << "4. Exit (button)\n";
    int number;
    std::cin >> number;
    if (number == 2) {
        std::cout << "Input the number of the client\n";
        int n;
        std::cin >> n;
        deal_list_window(manager, n - 1);
    }
    if (number == 3) { addClient_window(manager); }
    if (number == 4) { general_window(manager); }
    assert(false);
}*/

void LoginWindow::LoginManager() {
    std::string email, password;
    email = getEmail().toStdString();
    password = getPassword().toStdString();
    people::Manager manager;
    if (!people::is_correct_password(email, password)) {
        //std::cerr << "Incorrect password\n";
        //login_window();
        //TODO окно ошибки
    }
    try {
        people::get_manager(manager, email);
    } catch (const std::exception& e) {
        //std::cerr << "Such user is not exists. Try again\n";
        //TODO окно ошибки
    }
    mainwind->SetManager(manager);
    mainwind->ChangeToGeneral();
}

void RegisterWindow::RegisterManager() {
    std::string name, phone, email, pass;
    email = getEmail().toStdString();
    name = getName().toStdString();
    phone = getPhone().toStdString();
    pass = getPassword().toStdString();
    while (name.empty() || phone.empty() || email.empty() || pass.empty()) {
        errwind.resize(1500, 1000);
        errwind.setWindowTitle("Empty field");
        errwind.show();
    }
    people::Manager manager(email, pass, name, phone);
    try {
        people::add_manager(manager);
    } catch (...) {
        //std::cerr << "Account already exists\n";
        mainwind->ChangeToStart();
        //TODO окно с ошибкой и вернуться назад
    }
    mainwind->SetManager(manager);
    mainwind->ChangeToGeneral();
}


/*void general_window(people::Manager &manager) {
    // open window
    std::cout << "Here is a general window. Here are some options:\n";
    std::cout << "1. Go to your manager account (button)\n";
    std::cout << "2. Go to the clients window (button)\n";
    std::cout << "3. Exit (button)\n";
    int number;
    std::cin >> number;
    if (number == 1) { manager_window(manager); }
    if (number == 2) { cilents_window(manager); }
    if (number == 3) { enter_window(); }
    assert(false);
}*/

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    //MainWindow main_window;
    //StartWindow start_window(&main_window);
    //LoginWindow login_window(&main_window);
    //RegisterWindow register_window(&main_window);
    //GeneralWindow general_window(&main_window);
    //ClientsList clients_list_window(&main_window);

    wd::main_window.addTab(&wd::start_window, "Start");
    wd::main_window.addTab(&wd::login_window, "Login");
    wd::main_window.addTab(&wd::register_window, "Registration");
    wd::main_window.addTab(&wd::general_window, "Main menu");
    //main_window.addTab(&clients_list_window, "ClientsList");

    wd::main_window.resize(2000, 1200);
    wd::main_window.setWindowTitle("CRM-system");
    wd::main_window.show();
    return app.exec();
}
