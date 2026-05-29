#include "Pair.h"

#include "file_work.h"
#include <iostream>
#include <clocale>
#include <limits>

using namespace std;

void showMenu() {
    cout << "\n========== МЕНЮ ==========" << endl;
    cout << "1. Создать файл" << endl;
    cout << "2. Просмотреть файл" << endl;
    cout << "3. Удалить записи < значения" << endl;
    cout << "4. Увеличить записи = значению на L" << endl;
    cout << "5. Добавить K записей после позиции" << endl;
    cout << "6. Добавить запись в конец" << endl;
    cout << "7. Очистить файл" << endl;
    cout << "0. Выход" << endl;
    cout << "Выбор: ";
}

// Функция для безопасного ввода числа
int safeInputInt() {
    int value;
    while (!(cin >> value)) {
        cin.clear(); // Сбрасываем ошибку
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очищаем буфер
        cout << "Ошибка! Введите число: ";
    }
    return value;
}

double safeInputDouble() {
    double value;
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка! Введите число: ";
    }
    return value;
}

int main() {
    setlocale(LC_ALL, "Russian");

    const char* filename = "pairs.txt";
    int choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            make_file(filename);
            break;

        case 2:
            print_file(filename);
            break;

        case 3: {
            Pair value;
            cout << "Введите значение: ";
            cin >> value;
            delete_less_than(filename, value);
            break;
        }

        case 4: {
            Pair value;
            double L;
            cout << "Введите значение для поиска: ";
            cin >> value;
            cout << "Введите число L: ";
            cin >> L;
            increase_by_value(filename, value, L);
            break;
        }

        case 5: {
            int pos, K;
            cout << "Позиция (0 - в начало): ";
            cin >> pos;
            cout << "Количество записей K: ";
            cin >> K;
            add_after_position(filename, pos, K);
            break;
        }

        case 6: {
            Pair p;
            cout << "Введите пару: ";
            cin >> p;
            add_to_end(filename, p);
            break;
        }

        case 7:
            clear_file(filename);
            break;

        case 0:
            cout << "До свидания!" << endl;
            break;

        default:
            cout << "Неверный выбор!" << endl;
        }
    } while (choice != 0);

    return 0;
}

