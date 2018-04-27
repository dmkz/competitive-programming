#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <cassert>
#include <functional>

struct Int;

std::istream& operator>>(std::istream&, Int&);
std::ostream& operator<<(std::ostream&, const Int&);
bool operator<(const Int&, const Int&);
bool operator>(const Int&, const Int&);
bool operator==(const Int&, const Int&);
bool operator<=(const Int&, const Int&);
bool operator>=(const Int&, const Int&);
bool operator!=(const Int&, const Int&);
Int operator+(const Int&, const Int&);
Int operator+(const int, const Int&);
Int operator-(const Int&, const Int&);
Int operator*(const int, const Int&);
Int operator/(const Int& a, const int);
int operator%(const Int& a, const int);
Int pow(Int, int);

struct Int {
    static const int BASE = (int)1e9; // Основание системы счисления
    static const int WIDTH = 9;       // Количество десятичных цифр, которые хранятся в одной цифре
    
    // Вектор под цифры числа:
    std::vector<int> digits; 
    
    // Нормализуем вид числа - удаляем лидирующие нули
    Int& to_normal() {
        while (digits.back() == 0 && (int)digits.size() > 1) {
            digits.pop_back();
        }
        return *this;
    }   
    
    // Конструктор от короткого целого
    Int (int64_t number = 0) {
        assert(number >= 0);
        do {
            digits.push_back(number % BASE);
            number /= BASE;
        } while (number > 0);
        to_normal();
    }
    
    // Конструктор от вектора из цифр:
    Int (const std::vector<int>& digits) : digits(digits) { to_normal(); }
    
    // Конструктор от строчки:
    Int (std::string s) {
        const int size = (int)s.size();
        for (int idGroup = 1, nGroups = size / WIDTH; idGroup <= nGroups; ++idGroup) {            
            digits.push_back(std::stoi(s.substr(size-idGroup * WIDTH, WIDTH)));
        }
        if (size % WIDTH != 0) {
            digits.push_back(std::stoi(s.substr(0, size % WIDTH)));
        }
        to_normal();
    }
    
    // Прибавление:
    Int& operator+=(const int num) {
        if (num >= BASE) {
            return *this += Int(num);
        } 
        int rem = num;
        for (int i = 0; rem > 0; ++i) {
            if (i >= size()) digits.push_back(0);
            rem += at(i);
            at(i) = rem % BASE;
            rem /= BASE;
        }
        return this->to_normal();
    }
    
    // Прибавление:
    Int& operator+=(const Int& other) {
        if (other.size() == 1) {
            return *this += other.at(0);
        }
        const int s1 = this->size();
        const int s2 = other.size();
        int rem = 0;
        for (int i = 0; i < s1 || i < s2 || rem > 0; ++i) {
            int d1 = i < s1 ? this->at(i) : 0;
            int d2 = i < s2 ? other.at(i) : 0;
            rem += d1 + d2;
            if (i >= s1) digits.push_back(0);
            at(i) = rem % BASE;
            rem /= BASE;
        }
        return this->to_normal();
    }
    
    // Вычитание короткого:
    Int& operator-=(const int num) {
        if (num >= BASE) {
            return *this -= Int(num);
        }
        int rem = -num;
        for (int i = 0; rem < 0; ++i) {
            assert(i < size());
            rem += at(i);
            if (rem < 0) {
                at(i) = (rem + BASE) % BASE;
                rem = -1;
            } else {
                at(i) = rem % BASE;
                rem = 0;
            }
        }
        return this->to_normal();
    }
    
    // Вычитание длинного:
    Int& operator-=(const Int& other) {
        if (other.size() == 1) {
            return *this -= other.at(0);
        }
        assert(*this >= other);
        const int s1 = this->size();
        const int s2 = other.size();
        int rem = 0;
        for (int i = 0; i < s1 || i < s2; ++i) {
            int d1 = i < s1 ? this->at(i) : 0;
            int d2 = i < s2 ? other.at(i) : 0;
            rem += d1 - d2;
            if (i >= s1) digits.push_back(0);
            if (rem < 0) {
                at(i) = (rem + BASE) % BASE;
                rem = -1;
            } else {
                at(i) = rem % BASE;
                rem = 0;
            }
        }
        return this->to_normal();
    }
    
    // Умножение на короткое:
    Int& operator*=(const int num) {
        // std::cout << "call Int& operator*=(const int num)" << std::endl;
        if (num >= BASE) {
            return *this *= Int(num);
        }
        int64_t rem = 0;
        for (int i = 0; i < size() || rem > 0; ++i) {
            // std::cout << "i = " << i << std::endl;
            if (i >= size()) digits.push_back(0);
            rem += 1LL * at(i) * num;
            at(i) = rem % BASE;
            rem /= BASE;
        }
        return this->to_normal();
    }
    
    // Умножение:
    Int operator*(const int num) const {
        return num >= BASE ? *this * Int(num) : Int(*this) *= num;
    }
    
    // Произведение:
    Int operator*(const Int& other) const {
        // std::cout << "call Int operator*(const Int& other)" << std::endl;
        if (other.size() == 1) {
            return *this * other.at(0);
        }
        const int s1 = this->size();
        const int s2 = other.size();
        std::vector<int> temp(s1+s2);
        for (int i = 0; i < s1; ++i) {
            int64_t rem = 0;
            for (int j = 0; j < s2; ++j) {
                rem += temp.at(i+j) + 1LL * this->at(i) * other.at(j);
                temp.at(i+j) = rem % BASE;
                rem /= BASE;
            }
            if (rem > 0) {
                temp.at(i+s2) += rem;
                assert(0 <= temp.at(i+s2) && temp.at(i+s2) < BASE);
            }
        }
        return Int(temp);
    }
    
    // Умножение:
    Int& operator*=(const Int& other) {
        // std::cout << "call Int& operator*=(const Int& other)" << std::endl;
        return other.size() == 1 ? *this *= other.at(0) : *this = *this * other;
    }
    
    // Деление на короткое:
    Int& operator/= (const int num) {
        // std::cout << "call Int& operator/= (const int num)" << std::endl;
        if (num >= BASE) {
            return *this /= Int(num);
        }
        assert(0 < num && num < BASE);
        int64_t rem = 0;
        for (int j = size()-1; j >= 0; --j) {
            // std::cout << "j = " << j << std::endl;
            (rem *= BASE) += at(j);
            // std::cout << "at(j) = " << at(j) << std::endl;
            at(j) = rem / num;
            assert(0 <= at(j) && at(j) < BASE);
            rem %= num;
        }
        // std::cout << "gool end!" << std::endl;
        return this->to_normal();
    }
    
    // Взятие остатка от деления:
    Int& operator%=(const int num) {
        return *this = *this % num;
    }
    
    static Int div(Int a, Int b) {
    // Данный метод работает за O(m*n)
    // Условия:
    // base^(m-1) <= a < base^m (1)
    // base^n / 2 <= b < base^n (2)
        // Условие (1) выполняется всегда для m = a.size()
        // Условие (2) необходимо обеспечить равносильным преобразованием следующим образом:
        if (2 * b.digits.back() < Int::BASE) {
            int d = (1LL * Int::BASE + 2 * b.digits.back() - 1) / (2 * b.digits.back());
            a *= d;
            b *= d;
        }

        const int n = b.size(), m = a.size();

        std::function<Int(Int, Int)> special_div = [&special_div](const Int& a, const Int& b) {
            // Данный метод работает за O(n), при следующих условиях:
            // 0 <= a <= base^(n+1)
            // b^n / 2 <= b < base^n
            const int n = b.size();
            // Проверки на соответствии условиям метода:
            assert(a.size() - b.size() == 1);
            if (a >= b * BASE) {
                return Int(BASE) + special_div(a-b * BASE, b);
            } else {
                int64_t q = (BASE * 1LL * a.at(n) + a.at(n-1)) / b.at(n-1);
                assert(0 <= q && q < BASE);
                auto t = q * b;
                if (t > a) { --q, t -= b; }
                if (t > a) { --q, t -= b; }
                assert(t <= a);
                return Int(q);
            }
        };     
        
        if (m < n) {
            return 0; // O(1)
        } else if (m == n) {
            return a >= b ? 1 : 0; // O(n)
        } else if (m == n+1) {
            return special_div(a, b); // O(n)
        } else {
            Int a_temp = std::vector<int>(a.digits.begin()+m-n-1, a.digits.begin()+m); // O(n)
            Int s = std::vector<int>(a.digits.begin(), a.digits.begin()+m-n-1); // O(n)
            Int q_temp = special_div(a_temp, b); // O(n)
            Int r_temp = a_temp - q_temp * b; // O(n)
            Int q = div(r_temp.shift_left(m-n-1)+s, b); // O(m-n) рекурсивных вызовов -> общая асимптотика O(m*n)
            return q_temp.shift_left(m-n-1) + q; // O(n)
        }
    }
    
    Int operator/(const Int& other) const {
        // std::cout << "call operator/(const Int& other)" << std::endl;
        return (other.size() == 1) ? *this / other.at(0) : div(*this, other);
    }
    
    Int& operator/=(const Int& other) {
        // std::cout << "call Int& operator/=(const Int& other)" << std::endl;
        return *this = *this / other;
    }
    
    Int operator%(const Int& other) const {
        // std::cout << "call operator%(const Int& other)" << std::endl;
        return *this - *this / other * other;
    }
    
    Int& operator%=(const Int& other) {
        return *this = *this % other;
    }
    
    // Сравнение: result < 0 (меньше), result == 0 (равно), result > 0 (больше)
    int compare(const Int& other) const {
        if (this->size() > other.size()) return 1;
        if (this->size() < other.size()) return -1;
        for (int i = size()-1; i >= 0; --i) {
            if (this->at(i) > other.at(i)) return 1;
            if (this->at(i) < other.at(i)) return -1;
        }
        return 0;
    }
    
    int& at(int pos) {
        assert(0 <= pos && pos < size());
        return digits.at(pos);
    }
    
    const int& at(int pos) const {
        assert(0 <= pos && pos < size());
        return digits.at(pos);
    }
    
    inline int size() const {
        return (int)digits.size();
    }
    
    Int& shift_left(int pow) {
        assert(pow >= 0);
        digits.resize((int)digits.size()+pow);
        for (int i = (int)digits.size()-1; i >= pow; --i) {
            digits[i] = digits[i-pow];
        }
        for (int i = pow-1; i >= 0; --i) {
            digits[i] = 0;
        }
        return to_normal();
    }
    
    Int& shift_right(int pow) {
        assert(pow >= 0);
        if (pow >= (int)digits.size()) {
            return *this = 0;
        }
        for (int i = 0; i + pow < (int)digits.size(); ++i) {
            digits[i] = digits[i+pow];
        }
        digits.resize((int)digits.size()-pow);
        return to_normal();
    }
};

// Ввод из потока:
std::istream& operator>>(std::istream& is, Int& number) {
    std::string s;
    is >> s;
    number = Int(s);
    return is;
}

// Вывод в поток:
std::ostream& operator<<(std::ostream& os, const Int& number) {
    os << number.digits.back();
    for (int i = (int)number.digits.size()-2; i >= 0; --i) {
        os << std::setw(Int::WIDTH) << std::setfill('0') << number.digits[i];
    }
    return os << std::setfill(' ');
}

// Сложение:
Int operator+(const Int& a, const Int& b) {
    return Int(a) += b;
}

// Вычитание:
Int operator-(const Int& a, const Int& b) {
    return Int(a) -= b;
}

// Умножение:
Int operator*(const int a, const Int& b) {
    return b * a;
}

// Деление:
Int operator/(const Int& a, const int num) {
    // std::cout << "operator/(const Int& a, const int num)" << std::endl;
    return Int(a) /= num;
}

// Остаток от деления:
int operator%(const Int& a, const int num) {
    int64_t rem = 0;
    for (int i = a.size()-1; i >= 0; --i) {
        ((rem *= Int::BASE) += a.at(i)) %= num;
    }
    return rem;
}

// Возведение в степень:
Int pow(Int a, int n) {
    Int res = 1;
    while (n > 0) {
        if (n % 2 != 0) {
            res *= a;
        }
        a *= a;
        n /= 2;
    }
    return res;
}

// Операторы сравнения:
bool operator<(const Int& a, const Int& b) { return a.compare(b) < 0; }
bool operator>(const Int& a, const Int& b) { return a.compare(b) > 0; }
bool operator==(const Int& a, const Int& b) { return a.compare(b) == 0; }
bool operator<=(const Int& a, const Int& b) { return a.compare(b) <= 0; }
bool operator>=(const Int& a, const Int& b) { return a.compare(b) >= 0; }
bool operator!=(const Int& a, const Int& b) { return a.compare(b) != 0; }

int main() {
    Int n, k; 
    std::cin >> n >> k;
    std::cout << n % k << std::endl;
    return 0;
}