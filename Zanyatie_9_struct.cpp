#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

enum ComfortType {
    LUX,           // Люкс
    SEMI_LUX,      // Полулюкс
    STANDARD,      // Стандарт
    ECONOM         // Эконом
};

// Структура с бытовыми опциями (вложенная структура)
struct RoomFacilities {
    bool hasSeaView;         // Вид на море
    bool hasWiFi;            // Wi-Fi
    bool hasAirConditioning; // Кондиционер
    bool hasMinibar;         // Минибар
    bool hasTV;              // Телевизор
};

// Основная структура гостиничного номера
struct HotelRoom {
    string hotelName;        // Название гостиницы
    int roomNumber;          // Номер комнаты
    ComfortType comfort;     // Уровень комфортности
    int maxGuests;           // Максимальное количество гостей
    double pricePerNight;    // Стоимость за ночь
    RoomFacilities facilities; // Бытовые опции
};

// Преобразование ComfortType в строку
string comfortToString(ComfortType level) {
    switch(level) {
        case LUX: return "Люкс";
        case SEMI_LUX: return "Полулюкс";
        case STANDARD: return "Стандарт";
        case ECONOM: return "Эконом";
        default: return "Неизвестно";
    }
}

// Вывод информации об одном номере
void printRoom(const HotelRoom& room) {
    cout << "Гостиница: " << room.hotelName << endl;
    cout << "Номер: " << room.roomNumber << endl;
    cout << "Категория: " << comfortToString(room.comfort) << endl;
    cout << "Максимум гостей: " << room.maxGuests << endl;
    cout << "Цена за ночь: $" << room.pricePerNight << endl;
    cout << "Удобства:" << endl;
    cout << "  - Вид на море: " << (room.facilities.hasSeaView ? "Да" : "Нет") << endl;
    cout << "  - Wi-Fi: " << (room.facilities.hasWiFi ? "Да" : "Нет") << endl;
    cout << "  - Кондиционер: " << (room.facilities.hasAirConditioning ? "Да" : "Нет") << endl;
    cout << "  - Минибар: " << (room.facilities.hasMinibar ? "Да" : "Нет") << endl;
    cout << "  - Телевизор: " << (room.facilities.hasTV ? "Да" : "Нет") << endl;
    cout << "------------------------" << endl;
}

// Проверка, заканчивается ли название на "plaza"
bool endsWithPlaza(const string& hotelName) {
    if (hotelName.length() < 5) return false;
    string ending = hotelName.substr(hotelName.length() - 5);
    transform(ending.begin(), ending.end(), ending.begin(), ::tolower);
    return ending == "plaza";
}

// Фильтрация номеров по окончанию "plaza"
int filterPlazaHotels(const HotelRoom source[], int sourceSize, HotelRoom destination[]) {
    int count = 0;
    for (int i = 0; i < sourceSize; i++) {
        if (endsWithPlaza(source[i].hotelName)) {
            destination[count] = source[i];
            count++;
        }
    }
    return count;
}

// Сортировка пузырьком по возрастанию цены
void bubbleSortByPrice(HotelRoom arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j].pricePerNight > arr[j + 1].pricePerNight) {
                HotelRoom temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Поиск номера по его номеру
int findRoomByNumber(const HotelRoom arr[], int size, int roomNum) {
    for (int i = 0; i < size; i++) {
        if (arr[i].roomNumber == roomNum) {
            return i;
        }
    }
    return -1;
}

// Вывод 3 самых дешевых номеров
void printThreeCheapest(const HotelRoom arr[], int size) {
    if (size < 3) {
        cout << "Недостаточно номеров для отображения топ-3" << endl;
        return;
    }
    
    cout << "\n=== 3 САМЫХ ДЕШЕВЫХ НОМЕРА ===" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "\n--- Место " << (i + 1) << " ---" << endl;
        printRoom(arr[i]);
        cout << "Бытовые опции: ";
        if (arr[i].facilities.hasSeaView) cout << "вид на море, ";
        if (arr[i].facilities.hasWiFi) cout << "Wi-Fi, ";
        if (arr[i].facilities.hasAirConditioning) cout << "кондиционер, ";
        if (arr[i].facilities.hasMinibar) cout << "минибар, ";
        if (arr[i].facilities.hasTV) cout << "ТВ";
        cout << endl;
    }
}

// Изменение данных конкретного номера
void updateRoomData(HotelRoom arr[], int size, int roomNum) {
    int index = findRoomByNumber(arr, size, roomNum);
    if (index == -1) {
        cout << "Номер " << roomNum << " не найден!" << endl;
        return;
    }
    
    cout << "\nИзменение данных для номера " << roomNum << ":" << endl;
    cout << "Введите новую цену за ночь: ";
    cin >> arr[index].pricePerNight;
    cout << "Введите максимальное количество гостей: ";
    cin >> arr[index].maxGuests;
    
    cout << "Данные успешно обновлены!" << endl;
}

// Фильтрация номеров с видом на море
int filterSeaViewRooms(const HotelRoom source[], int sourceSize, HotelRoom destination[]) {
    int count = 0;
    for (int i = 0; i < sourceSize; i++) {
        if (source[i].facilities.hasSeaView) {
            destination[count] = source[i];
            count++;
        }
    }
    return count;
}

// Оберточная функция для вывода отфильтрованных данных
void displayFilteredResults(const HotelRoom arr[], int size, const string& title) {
    cout << "\n=== " << title << " (найдено: " << size << ") ===" << endl;
    if (size == 0) {
        cout << "Нет данных для отображения" << endl;
        return;
    }
    
    for (int i = 0; i < size; i++) {
        cout << "\n--- Запись #" << (i + 1) << " ---" << endl;
        printRoom(arr[i]);
    }
}

// Инициализация массива данными
void initializeRooms(HotelRoom rooms[], int size) {
    rooms[0] = {"Grand Plaza", 101, LUX, 2, 15000, {true, true, true, true, true}};
    rooms[1] = {"Sea View Plaza", 205, SEMI_LUX, 3, 12000, {true, true, true, false, true}};
    rooms[2] = {"City Hotel", 302, STANDARD, 2, 5000, {false, true, true, false, true}};
    rooms[3] = {"Royal Plaza", 108, LUX, 4, 18000, {true, true, true, true, true}};
    rooms[4] = {"Comfort Inn", 415, ECONOM, 1, 3000, {false, true, false, false, true}};
    rooms[5] = {"Beach Plaza", 501, SEMI_LUX, 2, 11000, {true, true, true, true, true}};
    rooms[6] = {"Mountain Resort", 203, STANDARD, 3, 6000, {false, true, true, false, true}};
    rooms[7] = {"Sunset Plaza", 310, LUX, 2, 16000, {true, true, true, true, true}};
    rooms[8] = {"Downtown Hotel", 118, ECONOM, 2, 3500, {false, true, false, false, true}};
    rooms[9] = {"Ocean Plaza", 422, STANDARD, 4, 8000, {true, true, true, false, true}};
    rooms[10] = {"Garden Hotel", 305, SEMI_LUX, 2, 9000, {false, true, true, true, true}};
    rooms[11] = {"Star Plaza", 201, ECONOM, 1, 4000, {false, true, false, false, true}};
    rooms[12] = {"Lake View", 412, STANDARD, 3, 7000, {true, true, true, false, true}};
    rooms[13] = {"Central Plaza", 508, LUX, 2, 14000, {false, true, true, true, true}};
    rooms[14] = {"Airport Hotel", 115, ECONOM, 2, 3200, {false, true, false, false, true}};
    rooms[15] = {"Holiday Plaza", 320, SEMI_LUX, 3, 10000, {true, true, true, false, true}};
    rooms[16] = {"Park Hotel", 225, STANDARD, 2, 5500, {false, true, true, false, true}};
    rooms[17] = {"Marina Plaza", 401, LUX, 4, 17000, {true, true, true, true, true}};
    rooms[18] = {"Valley Inn", 318, ECONOM, 1, 2800, {false, false, false, false, true}};
    rooms[19] = {"Executive Plaza", 512, SEMI_LUX, 2, 13000, {true, true, true, true, true}};
}

int main() {
    setlocale(LC_ALL, "Russian");
    
    const int TOTAL_ROOMS = 20;
    HotelRoom allRooms[TOTAL_ROOMS];
    
    // Инициализация данных
    initializeRooms(allRooms, TOTAL_ROOMS);
    
    cout << "=== ВСЕ НОМЕРА ОТЕЛЕЙ (20 записей) ===" << endl;
    for (int i = 0; i < TOTAL_ROOMS; i++) {
        cout << "\n--- Номер " << (i + 1) << " ---" << endl;
        printRoom(allRooms[i]);
    }
    
    // Фильтрация отелей с окончанием "plaza"
    HotelRoom plazaRooms[TOTAL_ROOMS];
    int plazaCount = filterPlazaHotels(allRooms, TOTAL_ROOMS, plazaRooms);
    
    cout << "\n\n=== НОМЕРА В ОТЕЛЯХ С ОКОНЧАНИЕМ 'plaza' ===" << endl;
    cout << "Найдено: " << plazaCount << " записей" << endl;
    for (int i = 0; i < plazaCount; i++) {
        cout << "\n--- Запись #" << (i + 1) << " ---" << endl;
        printRoom(plazaRooms[i]);
    }
    
    // Сортировка по возрастанию цены
    bubbleSortByPrice(plazaRooms, plazaCount);
    
    cout << "\n\n=== ПОСЛЕ СОРТИРОВКИ ПО ЦЕНЕ (по возрастанию) ===" << endl;
    for (int i = 0; i < plazaCount; i++) {
        cout << "\n--- Позиция " << (i + 1) << " (цена: $"
             << plazaRooms[i].pricePerNight << ") ---" << endl;
        printRoom(plazaRooms[i]);
    }
    
    // Поиск и вывод конкретного номера
    int searchRoomNumber = 108;
    int foundIndex = findRoomByNumber(plazaRooms, plazaCount, searchRoomNumber);
    if (foundIndex != -1) {
        cout << "\n\n=== НАЙДЕННЫЙ НОМЕР " << searchRoomNumber << " ===" << endl;
        printRoom(plazaRooms[foundIndex]);
    } else {
        cout << "\nНомер " << searchRoomNumber << " не найден!" << endl;
    }
    
    // Вывод 3 самых дешевых номеров
    printThreeCheapest(plazaRooms, plazaCount);
    
    // Изменение данных номера
    cout << "\n\n=== ОБНОВЛЕНИЕ ДАННЫХ ===" << endl;
    updateRoomData(plazaRooms, plazaCount, 108);
    cout << "\nОбновленные данные:" << endl;
    foundIndex = findRoomByNumber(plazaRooms, plazaCount, 108);
    if (foundIndex != -1) {
        printRoom(plazaRooms[foundIndex]);
    }
    
    // Фильтрация номеров с видом на море
    HotelRoom seaViewRooms[TOTAL_ROOMS];
    int seaViewCount = filterSeaViewRooms(allRooms, TOTAL_ROOMS, seaViewRooms);
    
    // Вывод через оберточную функцию
    displayFilteredResults(seaViewRooms, seaViewCount, "НОМЕРА С ВИДОМ НА МОРЕ");
    
    return 0;
}

