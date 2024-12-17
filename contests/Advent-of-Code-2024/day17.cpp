#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using ll = long long;
namespace std {
    template<typename T>
    std::string to_string(const std::vector<T> &a) {
        std::string s;
        for (int i = 0; i < isz(a); i++) {
            if (i > 0) s += ',';
            s += std::to_string(a[i]);
        }
        return s;
    }
}
const bool debug = false;
void part1() {
    // форматированное чтение:
    ll a, b, c;
    int code = scanf(" Register A: %lld", &a);
    assert(code == 1);
    code = scanf(" Register B: %lld", &b);
    assert(code == 1);
    code = scanf(" Register C: %lld", &c);
    assert(code == 1);
    // читаем и конвертим буффер в вектор из чисел:
    auto data = [&](){
        char buffer[1001];
        code = scanf(" Program: %s", buffer);
        assert(code == 1);
        strcat(buffer, ",");
        if (debug) printf("buffer = '%s'\n", buffer);
        std::vector<int> result;
        std::istringstream ss(buffer);
        //ss << ",";
        int x; char ch;
        while (ss >> x >> ch) {
            assert(ch == ',');
            result.push_back(x);
            if (debug) printf("x = %d, ch = '%c'\n", x, ch);
        }
        return result;
    }();
    
    // выполняем программу
    // вспомогательная функция для определения значения комбинированного операнда
    auto getCombinedOperand = [&](int operand) -> ll
    {
        switch (operand) {
            case 0 ... 3: return operand;
            case 4: return a;
            case 5: return b;
            case 6: return c;
            case 7: assert(false);
        };
        return -1;
    };
    std::vector<int> answ;
    int ip = 0;
    auto print = [&](){
        if (debug) {
            printf("Register A: %lld\n", a);
            printf("Register B: %lld\n", b);
            printf("Register C: %lld\n", c);
            printf("Program: %s, ip = %d\n", to_string(data).c_str(), ip);
        }
    };
    print();
    while (ip < isz(data)) {
        int command = data[ip++];
        int operand = data[ip++];
        switch (command) {
            case 0: { // деление на степень двойки = сдвиг вправо
                a >>= getCombinedOperand(operand);
                break;
            }
            case 1: {
                b ^= operand;
                break;
            }
            case 2: {
                b = getCombinedOperand(operand) & 7;
                break;
            }
            case 3: {
                if (a)
                    ip = operand;
                break;
            }
            case 4: {
                b ^= c;
                break;
            }
            case 5: {
                answ.push_back(getCombinedOperand(operand) & 7);
                break;
            }
            case 6: { // деление на степень двойки = сдвиг вправо
                b = (a >> getCombinedOperand(operand));
                break;
            }
            case 7: { // деление на степень двойки = сдвиг вправо
                c = (a >> getCombinedOperand(operand));
                break;
            }
        };
        print();
    }
    for (int i = 0; i < isz(answ); i++) {
        if (i > 0) std::cout << ",";
        std::cout << answ[i];
    }
    std::cout << std::endl;
}
/* анализ программы
    Register A: 37293246
    Register B: 0
    Register C: 0

    Program: 2,4,1,6,7,5,4,4,1,7,0,3,5,5,3,0
    while (A) {     // 3,0
        B = A % 8;  // 2,4
        B ^= 6;     // 1,6
        C = A >> B; // 7,5
        B ^= C;     // 4,4
        B ^= 7;     // 1,7
        A >>= 3;    // 0,3
        answ.push_back(B % 8); // 5,5
    }
    
    сокращаем:
    while (A) {             // 3,0
        B = (A % 8) ^ 6;    // 2,4; 1,6;
        B ^= (A >> B) ^ 7;  // 7,5; 4,4; 1,7
        A >>= 3;            // 0,3
        answ.push_back(B % 8); // 5,5
    }
*/
void part1Analyzed(int64_t A = 37293246) {
    int64_t B{};
    static const std::vector<int> data{2,4,1,6,7,5,4,4,1,7,0,3,5,5,3,0};
    std::vector<int> answ;
    while (A) {             // 3,0
        B = (A % 8) ^ 6;    // 2,4; 1,6;
        B ^= (A >> B) ^ 7;  // 7,5; 4,4; 1,7
        A >>= 3;            // 0,3
        answ.push_back(B % 8); // 5,5
    }
    std::cout << std::to_string(answ) << std::endl;
}
// пытаемся подобрать разряды
int part1AnalyzedMatching(int64_t A) {
    int64_t B{};
    static const std::vector<int> data{2,4,1,6,7,5,4,4,1,7,0,3,5,5,3,0};
    int i = 0;
    while (A && i < isz(data)) {    // 3,0
        B = (A % 8) ^ 6;            // 2,4; 1,6;
        B ^= (A >> B) ^ 7;          // 7,5; 4,4; 1,7
        A >>= 3;                    // 0,3
        if (B % 8 != data[i]) {
            return i;
        }
        i++;
    }
    return i;
}
void researchMatching() {
// сначала запускаем без без суффикса, чтобы набрать как можно больше цифр
// в моём примере число AA = 55356306 позволяет набрать 7 цифр
// дальше мы будет дописывать это число ко все перебираемым (справа)
// чтобы набрать побольше цифр. В двоичной записи дописываем
// 0b11010011001010101110010010 (26 разрядов)
    int max = 1;
    for (int64_t AA = 0; ; AA++) {
        int64_t A = (AA << 26) | 0b11010011001010101110010010;
        int result = part1AnalyzedMatching(A);
        if (result > max) {
            std::cout << std::bitset<64>(A) << ", A = " << A << ", result = " << result << std::endl;
            max = result;
        }
    }
}
main() {
    researchMatching();
}

