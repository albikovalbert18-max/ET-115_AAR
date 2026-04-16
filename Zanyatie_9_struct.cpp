#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <fstream>
using namespace std;

enum ComfortType { LUX, SEMI_LUX, STANDARD, ECONOM };

struct Facilities {
    bool seaView, wifi, airCond, minibar, tv;
};

struct HotelRoom {
    string hotel;
    int roomNum;
    ComfortType comfort;
    int maxGuests;
    double price;
    int rating;
    Facilities fac;
};

string comfortStr(ComfortType c) {
    switch(c) {
        case LUX: return "Люкс";
        case SEMI_LUX: return "Полулюкс";
        case STANDARD: return "Стандарт";
        case ECONOM: return "Эконом";
        default: return "?";
    }
}

void printRoom(const HotelRoom& r) {
    cout << "Отель: " << r.hotel << endl;
    cout << "Номер: " << r.roomNum << endl;
    cout << "Тип: " << comfortStr(r.comfort) << endl;
    cout << "Гостей: " << r.maxGuests << endl;
    cout << "Цена: $" << r.price << endl;
    cout << "Рейтинг: " << r.rating << "/10" << endl;
    cout << "Удобства: ";
    if (r.fac.seaView) cout << "вид на море, ";
    if (r.fac.wifi) cout << "Wi-Fi, ";
    if (r.fac.airCond) cout << "кондиционер, ";
    if (r.fac.minibar) cout << "минибар, ";
    if (r.fac.tv) cout << "ТВ";
    cout << "\n-------------------\n";
}

bool isPlaza(string name) {
    if (name.length() < 5) return false;
    string end = name.substr(name.length() - 5);
    transform(end.begin(), end.end(), end.begin(), ::tolower);
    return end == "plaza";
}

int filterPlaza(HotelRoom src[], int n, HotelRoom dst[]) {
    int cnt = 0;
    for (int i = 0; i < n; i++)
        if (isPlaza(src[i].hotel))
            dst[cnt++] = src[i];
    return cnt;
}

void sortPrice(HotelRoom arr[], int n) {
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (arr[j].price > arr[j+1].price) {
                HotelRoom tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
}

int findRoom(HotelRoom arr[], int n, int num) {
    for (int i = 0; i < n; i++)
        if (arr[i].roomNum == num) return i;
    return -1;
}

void initData(HotelRoom r[], int n) {
    r[0] = {"Grand Plaza", 101, LUX, 2, 15000, 0, {true, true, true, true, true}};
    r[1] = {"Sea View Plaza", 205, SEMI_LUX, 3, 12000, 0, {true, true, true, false, true}};
    r[2] = {"City Hotel", 302, STANDARD, 2, 5000, 0, {false, true, true, false, true}};
    r[3] = {"Royal Plaza", 108, LUX, 4, 18000, 0, {true, true, true, true, true}};
    r[4] = {"Comfort Inn", 415, ECONOM, 1, 3000, 0, {false, true, false, false, true}};
    r[5] = {"Beach Plaza", 501, SEMI_LUX, 2, 11000, 0, {true, true, true, true, true}};
    r[6] = {"Mountain Resort", 203, STANDARD, 3, 6000, 0, {false, true, true, false, true}};
    r[7] = {"Sunset Plaza", 310, LUX, 2, 16000, 0, {true, true, true, true, true}};
    r[8] = {"Downtown Hotel", 118, ECONOM, 2, 3500, 0, {false, true, false, false, true}};
    r[9] = {"Ocean Plaza", 422, STANDARD, 4, 8000, 0, {true, true, true, false, true}};
    r[10] = {"Garden Hotel", 305, SEMI_LUX, 2, 9000, 0, {false, true, true, true, true}};
    r[11] = {"Star Plaza", 201, ECONOM, 1, 4000, 0, {false, true, false, false, true}};
    r[12] = {"Lake View", 412, STANDARD, 3, 7000, 0, {true, true, true, false, true}};
    r[13] = {"Central Plaza", 508, LUX, 2, 14000, 0, {false, true, true, true, true}};
    r[14] = {"Airport Hotel", 115, ECONOM, 2, 3200, 0, {false, true, false, false, true}};
    r[15] = {"Holiday Plaza", 320, SEMI_LUX, 3, 10000, 0, {true, true, true, false, true}};
    r[16] = {"Park Hotel", 225, STANDARD, 2, 5500, 0, {false, true, true, false, true}};
    r[17] = {"Marina Plaza", 401, LUX, 4, 17000, 0, {true, true, true, true, true}};
    r[18] = {"Valley Inn", 318, ECONOM, 1, 3800, 0, {false, false, false, false, true}};
    r[19] = {"Executive Plaza", 512, SEMI_LUX, 2, 13000, 0, {true, true, true, true, true}};
}

// ЗАДАНИЕ 1: ЗАПИСЬ рейтингов в файл
void writeRatingsToFile(HotelRoom r[], int n, string file) {
    ofstream fout(file);
    cout << "\n=== ЗАПИСЬ РЕЙТИНГОВ В ФАЙЛ ===" << endl;
    
    // Записываем некоторые номера с рейтингами
    fout << "101 9" << endl;
    fout << "108 10" << endl;
    fout << "205 8" << endl;
    fout << "201 6" << endl;
    fout << "302 6" << endl;
    fout << "415 5" << endl;
    fout << "501 8" << endl;
    fout << "310 9" << endl;
    fout.close();
    
    cout << "Рейтинги записаны в " << file << endl;
}

// ЗАДАНИЕ 1: ЧТЕНИЕ рейтингов из файла
void readRatingsFromFile(HotelRoom r[], int n, string file) {
    ifstream fin(file);
    if (!fin.is_open()) {
        cout << "Файл не найден!" << endl;
        return;
    }
    
    cout << "\n ЧТЕНИЕ РЕЙТИНГОВ ИЗ ФАЙЛА" << endl;
    int num, rat, cnt = 0;
    
    while (fin >> num >> rat) {
        for (int i = 0; i < n; i++) {
            if (r[i].roomNum == num) {
                r[i].rating = rat;
                cout << "Номер " << num << " -> рейтинг " << rat << endl;
                cnt++;
                break;
            }
        }
    }
    fin.close();
    cout << "Обновлено: " << cnt << " записей\n" << endl;
}

// ЗАДАНИЕ 2: Запись в бинарный файл
void saveBin(HotelRoom r[], int n, string file) {
    ofstream fout(file, ios::binary);
    fout.write((char*)&n, sizeof(n));
    
    for (int i = 0; i < n; i++) {
        int len = r[i].hotel.length();
        fout.write((char*)&len, sizeof(len));
        fout.write(r[i].hotel.c_str(), len);
        fout.write((char*)&r[i].roomNum, sizeof(r[i].roomNum));
        fout.write((char*)&r[i].comfort, sizeof(r[i].comfort));
        fout.write((char*)&r[i].maxGuests, sizeof(r[i].maxGuests));
        fout.write((char*)&r[i].price, sizeof(r[i].price));
        fout.write((char*)&r[i].rating, sizeof(r[i].rating));
        fout.write((char*)&r[i].fac, sizeof(r[i].fac));
    }
    fout.close();
    cout << "Данные сохранены в " << file << endl;
}

// ЗАДАНИЕ 2: Чтение из бинарного файла
void loadBin(HotelRoom r[], int &n, string file) {
    ifstream fin(file, ios::binary);
    if (!fin.is_open()) {
        cout << "Файл " << file << " не найден!" << endl;
        return;
    }
    
    fin.read((char*)&n, sizeof(n));
    cout << "\n=== ЗАГРУЗКА ИЗ БИНАРНОГО ФАЙЛА ===" << endl;
    cout << "Записей: " << n << endl;
    
    for (int i = 0; i < n; i++) {
        int len;
        fin.read((char*)&len, sizeof(len));
        char* buf = new char[len + 1];
        fin.read(buf, len);
        buf[len] = '\0';
        r[i].hotel = buf;
        delete[] buf;
        
        fin.read((char*)&r[i].roomNum, sizeof(r[i].roomNum));
        fin.read((char*)&r[i].comfort, sizeof(r[i].comfort));
        fin.read((char*)&r[i].maxGuests, sizeof(r[i].maxGuests));
        fin.read((char*)&r[i].price, sizeof(r[i].price));
        fin.read((char*)&r[i].rating, sizeof(r[i].rating));
        fin.read((char*)&r[i].fac, sizeof(r[i].fac));
    }
    fin.close();
    cout << "Данные загружены из " << file << "\n" << endl;
}

// ОБНОВЛЕНИЕ данных номера
void updateRoom(HotelRoom r[], int n, int num) {
    int idx = findRoom(r, n, num);
    if (idx == -1) {
        cout << "Номер " << num << " не найден!" << endl;
        return;
    }
    
    cout << "\n=== ОБНОВЛЕНИЕ НОМЕРА " << num << " ===" << endl;
    cout << "Текущая цена: $" << r[idx].price << endl;
    cout << "Новая цена: $";
    cin >> r[idx].price;
    
    cout << "Текущее кол-во гостей: " << r[idx].maxGuests << endl;
    cout << "Новое кол-во гостей: ";
    cin >> r[idx].maxGuests;
    
    cout << "Текущий рейтинг: " << r[idx].rating << endl;
    cout << "Новый рейтинг (1-10): ";
    cin >> r[idx].rating;
    
    cout << "Данные обновлены!\n" << endl;
}

// Вывод 3 самых дешевых
void printTop3(HotelRoom r[], int n) {
    if (n < 3) {
        cout << "Недостаточно данных" << endl;
        return;
    }
    
    cout << "\n=== 3 САМЫХ ДЕШЕВЫХ ===" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "\n--- Место " << (i+1) << " ---" << endl;
        printRoom(r[i]);
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    const int N = 20;
    HotelRoom rooms[N];
    
    initData(rooms, N);
    
    cout << "=== ВСЕ НОМЕРА ===" << endl;
    for (int i = 0; i < N; i++) {
        cout << "\n--- " << (i+1) << " ---" << endl;
        printRoom(rooms[i]);
    }
    
    // ЗАДАНИЕ 1:ЗАПИСЫВАЕМ рейтинги в файл
    writeRatingsToFile(rooms, N, "ratings.txt");
    
    // ЗАДАНИЕ 1:ЧИТАЕМ их обратно
    readRatingsFromFile(rooms, N, "ratings.txt");
    
    // ЗАДАНИЕ 2: Сохраняем в бинарный файл
    saveBin(rooms, N, "data.bin");
    
    // ЗАДАНИЕ 2: Загружаем из бинарного файла
    HotelRoom loaded[N];
    int loadedN = 0;
    loadBin(loaded, loadedN, "data.bin");
    
    // Проверяем
    cout << "\nПРОВЕРКА (первые 2 из файла)" << endl;
    for (int i = 0; i < 2 && i < loadedN; i++)
        printRoom(loaded[i]);
    
    // Фильтрация Plaza
    HotelRoom plaza[N];
    int pCnt = filterPlaza(rooms, N, plaza);
    
    cout << "\n ОТЕЛИ PLAZA (" << pCnt << ")" << endl;
    for (int i = 0; i < pCnt; i++)
        printRoom(plaza[i]);
    
    // Сортировка по цене
    sortPrice(plaza, pCnt);
    cout << "\n PLAZA ПО ЦЕНЕ (возрастание)" << endl;
    for (int i = 0; i < pCnt; i++)
        printRoom(plaza[i]);
    
    // Поиск номера 108
    int idx = findRoom(plaza, pCnt, 108);
    if (idx != -1) {
        cout << "\n=== НАЙДЕН НОМЕР 108 ===" << endl;
        printRoom(plaza[idx]);
    }
    
    // Топ-3 самых дешевых
    printTop3(plaza, pCnt);
    
    // ОБНОВЛЕНИЕ данных
    updateRoom(plaza, pCnt, 108);
    
    cout << "\n=== ОБНОВЛЕННЫЙ НОМЕР 108 ===" << endl;
    idx = findRoom(plaza, pCnt, 108);
    if (idx != -1)
        printRoom(plaza[idx]);
    
    return 0;
}
