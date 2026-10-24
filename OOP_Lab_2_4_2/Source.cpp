#include <iostream>
#include <windows.h>
#include "Money.h"

// Структура для перевірки #pragma pack(1)
#pragma pack(push, 1)
struct NotePacked {
    Nominal nominal;
    int noteCount;
};
class MoneyPacked {
    int size_val;
    int count;
    NotePacked notes[10];
};
#pragma pack(pop)

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "--- Перевірка розміру класу ---" << endl;
    cout << "Розмір класу Money без #pragma pack(1): " << sizeof(Money) << " байт" << endl;
    cout << "Розмір класу з #pragma pack(1): " << sizeof(MoneyPacked) << " байт\n" << endl;

    // 1. Демонстрація конструкторів
    Money wallet1; // за умовчанням
    wallet1.addNote(N_100, 2);
    wallet1.addNote(N_10, 5); // Додаємо менший номінал пізніше
    cout << "wallet1 (перевірка сортування номіналів): \n" << wallet1 << endl;

    Money wallet2("500:1,50:3"); // ініціалізація рядком
    cout << "wallet2 (з рядка): \n" << wallet2 << endl;

    Money wallet3(wallet2); // копіювання
    cout << "wallet3 (копія wallet2): \n" << wallet3 << endl;

    // 2. Масив об'єктів
    cout << "\n--- Масив об'єктів ---" << endl;
    Money arr[2] = { Money("100:1"), Money("20:5") };
    for (int i = 0; i < 2; i++) {
        cout << "arr[" << i << "] = " << arr[i] << endl;
    }

    // 3. Дружні бінарні операції
    cout << "\n--- Операції додавання та порівняння ---" << endl;
    Money sum = wallet1 + wallet2;
    cout << "wallet1 + wallet2 = \n" << sum << endl;
    cout << "arr[0] == arr[1] (100 грн та 5 по 20 грн)? "
        << (arr[0] == arr[1] ? "Так" : "Ні") << endl;

    // 4. Індексування[] та присвоєння=
    cout << "\n--- Індексування та присвоєння ---" << endl;
    wallet1[0].noteCount = 10; // Зміна кількості найменшого номіналу
    cout << "wallet1 після зміни кількості через []: \n" << wallet1 << endl;

    wallet3 = wallet1;
    cout << "wallet3 після присвоєння wallet1: \n" << wallet3 << endl;

    // 5. Введення з клавіатури
    cout << "\n--- Введення з клавіатури ---" << endl;
    Money wallet4(5); // Макс 5 елементів
    cin >> wallet4;
    cout << "Ви ввели: " << wallet4 << endl;

    return 0;
}