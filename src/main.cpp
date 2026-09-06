#include "client.hpp"
int main() {
    int option = -1;
    s21::Client cl = s21::Client();
    while (option != 0) {
        cl.printMenu();
        if (!(std::cin >> option)) {
            std::cout << "Invalid option.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        cl.processSignal(option);
    }
    return 0;
}