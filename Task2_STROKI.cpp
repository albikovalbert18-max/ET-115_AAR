#include <iostream>
#include <string>
using namespace std;

int main() {
    string str;
    cout << "Введите строку: ";
    cin >> str;
    for (int i = 0; i < str.length(); i++) {
        char c = str[i];
        if (!(c >= '0' && c <= '9') &&
            !(c >= 'A' && c <= 'F') &&
            !(c >= 'a' && c <= 'f')) {
            cout << "Это НЕ шестнадцатеричное число" << endl;
            return 0;
        }
    }
    cout << "Это шестнадцатеричное число" << endl;
    return 0;
}
