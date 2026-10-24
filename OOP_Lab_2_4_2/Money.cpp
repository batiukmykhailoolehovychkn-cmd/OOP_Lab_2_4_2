#include "Money.h"
#include <sstream>
#include <cstdlib>

// Сортування вставкою: менший номінал на менший індекс
void Money::SortNotes() {
    for (int i = 1; i < count; ++i) {
        Note key = notes[i];
        int j = i - 1;
        while (j >= 0 && notes[j].nominal > key.nominal) {
            notes[j + 1] = notes[j];
            j = j - 1;
        }
        notes[j + 1] = key;
    }
}

Money::Money() : size_val(MAX_SIZE), count(0) {}

Money::Money(int s) : count(0) {
    size_val = (s > 0 && s <= MAX_SIZE) ? s : MAX_SIZE;
}

Money::Money(const Money& other) : size_val(other.size_val), count(other.count) {
    for (int i = 0; i < count; ++i) {
        notes[i] = other.notes[i];
    }
}

// Формат рядка: "номінал:кількість,номінал:кількість" (наприклад "10:5,50:2")
Money::Money(const string& strInit) : size_val(MAX_SIZE), count(0) {
    stringstream ss(strInit);
    string token;
    while (getline(ss, token, ',')) {
        size_t pos = token.find(':');
        if (pos != string::npos) {
            int nomVal = stoi(token.substr(0, pos));
            int cntVal = stoi(token.substr(pos + 1));
            addNote(static_cast<Nominal>(nomVal), cntVal);
        }
    }
}

int Money::getSize() const { return size_val; }
int Money::getCount() const { return count; }

long Money::getTotalSum() const {
    long sum = 0;
    for (int i = 0; i < count; ++i) {
        sum += notes[i].nominal * notes[i].noteCount;
    }
    return sum;
}

void Money::addNote(Nominal nom, int cnt) {
    if (cnt < 0) {
        cerr << "Кількість не може бути від'ємною!" << endl;
        return;
    }
    // Перевіряємо, чи такий номінал вже є
    for (int i = 0; i < count; ++i) {
        if (notes[i].nominal == nom) {
            notes[i].noteCount += cnt;
            return;
        }
    }
    // Додаємо новий номінал
    if (count < size_val) {
        notes[count].nominal = nom;
        notes[count].noteCount = cnt;
        count++;
        SortNotes(); // Підтримуємо порядок
    }
    else {
        cerr << "Масив переповнений, неможливо додати номінал!" << endl;
    }
}

Money& Money::operator=(const Money& other) {
    if (this != &other) {
        size_val = other.size_val;
        count = other.count;
        for (int i = 0; i < count; ++i) {
            notes[i] = other.notes[i];
        }
    }
    return *this;
}

Note& Money::operator[](int index) {
    if (index < 0 || index >= count) {
        cerr << "Індекс поза межами!" << endl;
        exit(1);
    }
    return notes[index];
}

const Note& Money::operator[](int index) const {
    if (index < 0 || index >= count) {
        cerr << "Індекс поза межами!" << endl;
        exit(1);
    }
    return notes[index];
}

Money::operator string() const {
    stringstream ss;
    ss << "Загальна сума: " << getTotalSum() << " грн [ ";
    for (int i = 0; i < count; ++i) {
        ss << notes[i].nominal << "грн x" << notes[i].noteCount;
        if (i < count - 1) ss << ", ";
    }
    ss << " ]";
    return ss.str();
}

Money operator+(const Money& left, const Money& right) {
    Money result = left;
    for (int i = 0; i < right.count; ++i) {
        result.addNote(right.notes[i].nominal, right.notes[i].noteCount);
    }
    return result;
}

bool operator==(const Money& left, const Money& right) {
    return left.getTotalSum() == right.getTotalSum();
}

ostream& operator<<(ostream& out, const Money& m) {
    out << string(m);
    return out;
}

istream& operator>>(istream& in, Money& m) {
    int n, nom, cnt;
    cout << "Скільки номіналів бажаєте ввести? (макс " << m.size_val << "): ";
    in >> n;
    if (n > m.size_val) n = m.size_val;

    m.count = 0; // Очищення перед вводом
    for (int i = 0; i < n; ++i) {
        cout << "Введіть номінал (1,2,5,10,20,50,100,200,500,1000): ";
        in >> nom;
        cout << "Введіть кількість купюр: ";
        in >> cnt;
        m.addNote(static_cast<Nominal>(nom), cnt);
    }
    return in;
}