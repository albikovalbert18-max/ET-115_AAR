#include <iostream>

using namespace std;

int main() {
    
    int n;
    cout << "Сколько чисел? ";
    cin >> n;

    
    int arr[100];

    
    cout << "Введите " << n << " чисел через пробел: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    cout << "Отсортировано: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    int target;
    cout << "Какое число найти? ";
    cin >> target;

    int left = 0;
    int right = n - 1;
    int result = -1; // -1 значит "не нашли"

    while (left <= right) {
        int mid = (left + right) / 2;

        if (arr[mid] == target) {
            result = mid; // Нашли
            break;
        }
        else if (arr[mid] < target) {
            left = mid + 1; // Ищем справа
        }
        else {
            right = mid - 1; // Ищем слева
        }
    }

    // Выводим результат
    if (result == -1) {
        cout << "Число " << target << " не найдено" << endl;
    }
    else {
        cout << "Число " << target << " на индексе " << result << endl;
    }

    return 0;
}
