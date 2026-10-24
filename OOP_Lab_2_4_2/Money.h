#pragma once
#include <iostream>
#include <string>

using namespace std;

// Переліковий тип для номіналів[cite: 164]
enum Nominal {
    N_1 = 1, N_2 = 2, N_5 = 5, N_10 = 10,
    N_20 = 20, N_50 = 50, N_100 = 100,
    N_200 = 200, N_500 = 500, N_1000 = 1000
};

// Структура, що описує купюру[cite: 164]
struct Note {
    Nominal nominal;
    int noteCount;
};

class Money {
private:
    static const int MAX_SIZE = 10; // Максимально можливий розмір масиву[cite: 161]
    int size_val;                   // Максимальна кількість елементів[cite: 161, 162]
    int count;                      // Фактична кількість елементів[cite: 162]
    Note notes[MAX_SIZE];           // Масив структур[cite: 164]

    // Допоміжний метод для сортування (менший індекс - менший номінал)[cite: 164]
    void SortNotes();

public:
    // Конструктори[cite: 161]
    Money();
    Money(int s);
    Money(const Money& other);
    Money(const string& strInit);   // Ініціалізація літерним рядком[cite: 162]

    // Методи доступу[cite: 161]
    int getSize() const;
    int getCount() const;
    void addNote(Nominal nom, int cnt);
    long getTotalSum() const;

    // Обов'язкові операції (методи класу)[cite: 161]
    Money& operator=(const Money& other);
    Note& operator[](int index);
    const Note& operator[](int index) const;
    operator string() const;

    // Бінарні операції (зовнішні дружні функції)[cite: 161]
    friend Money operator+(const Money& left, const Money& right);
    friend bool operator==(const Money& left, const Money& right);

    friend ostream& operator<<(ostream& out, const Money& m);
    friend istream& operator>>(istream& in, Money& m);
};