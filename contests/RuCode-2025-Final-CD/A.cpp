// Задача: A, Вердикт: OK, Время: 0.843 сек, Память: 4 МБ

// По определению мат. ожидания (сумма величин на их вероятность), ответ
// вычисляется по формуле: sum_{k=1}^15 (k * f(n, k) / 7^n),
// где k - длина максимальной римской подстроки, f(n, k) - количество строк
// длины n, для которых длина максимальной римской подстроки равна k
// Осталось посчитать f(n, k). Будем считать его динамическим программированием.
// dp[n][last][k] - количество строк длины n, оканчивающихся римским числом last,
// для которых длина максимальной римской подстроки равна k.
// Нам нужно хранить last, чтобы дописывать буквы в конец. Добавляя новую букву,
// мы получаем last + newChar, и после добавления новой буквы обновляем ответ
// Псевдокод:
// for длина in [1:n]:
//     for last in [0:3999]:
//         for newChar in ['M', 'D', 'C', 'L', 'X', 'V', 'I']:
//             for k in [0:15]:
//                newLast = макс римский суффикс(last+newChar)
//                newLastLen = его длина
//                dp[n][newLast][max(k, newLastLen)] += dp[n-1][last][k]
// Теперь f(n, k) = sum(dp[n][1:3999][k])
// Операций в худшем случае: 1000 * 4000 * 7 * 16 = 49 * 10^6 * 16 = 750 * 10^6
// Подробнее в реализации

#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>

#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()

void setmax(auto &x, const auto &y) { if (x < y) x = y; }

using namespace std;

// функция конвертации из десятичного в римское:
string toRoman(int x) {
    static const vector<pair<int,string>> table = {
        {1000,  "M"}, {900, "CM"}, {500,  "D"}, { 400, "CD"},
        { 100,  "C"}, { 90, "XC"}, { 50,  "L"}, {  40, "XL"},
        {  10,  "X"}, {  9, "IX"}, {  5,  "V"}, {   4, "IV"},
        {   1,  "I"}
    };
    string res;
    for (const auto &[n, s] : table)
        while (x >= n) {
            res += s;
            x -= n;
        }
    return res;
}

// список всех римских чисел:
const vector<string> roman = [](){
    vector<string> res(4000);
    for (int i = 1; i < 4000; i++)
        res[i] = toRoman(i);
    return res;
}();

// словарь: римское число -> десятичное число
const auto romanId = [](){
    map<string, int> res;
    for (int i = 0; i < 4000; i++)
        res[roman[i]] = i;
    return res;
}();

int getRomanId(const string &s) {
    auto it = romanId.find(s);
    if (it != romanId.end())
        return it->second;
    return -1;
}

const vector<char> letters = {'M', 'D', 'C', 'L', 'X', 'V', 'I'};

int letterId(char c) {
    return int(find(all(letters), c) - letters.begin());
}

// предподсчитываем переходы в будущей динамике:
const auto nextRoman = [](){
    // для каждого римского числа и для каждой новой буквы посчитаем переход:
    // какое максимальное новое римское число получается после добавления
    // этой буквы к текущему римскому числу справа
    vector result(4000, vector(isz(letters), 0));
    for (int num = 0; num < 4000; num++)
        for (int ic = 0; ic < isz(letters); ic++) {
            string s = roman[num] + letters[ic];
            for (int suff = isz(s); suff >= 0; suff--) {
                auto it = romanId.find(s.substr(isz(s)-suff, suff));
                if (it != romanId.end()) {
                    result[num][ic] = it->second;
                    break;
                }
            }
        }
    return result;
}();

// арифметика по модулю
const int mod = 998244353;

void modAddTo(int &x, const int y) {
    x += y;
    if (x >= mod)
        x -= mod;
}

int modMul(int x, int y) {
    return int(x * 1LL * y % mod);
}

int modPow(int a, int n) {
    int r = 1;
    while (n > 0) {
        if (n % 2 == 1)
            r = modMul(r, a);
        a = modMul(a, a);
        n >>= 1;
    }
    return r;
}

int modInv(int y) {
    return modPow(y, mod-2);
}

int modDiv(int x, int y) {
    return modMul(x, modInv(y));
}

// решение задачи:
int solve(int n) {
    // dp[n][lastRoman][maxAnswer]
    // для экономии памяти используем двуслойную динамику. Достаточно знать
    // dp[n] и dp[n-1]
    vector dpCurr(4000, vector(16, 0));
    auto dpNext = dpCurr;
    dpCurr[0][0] = 1;
    // операций в худшем случае: 1000 * 4000 * 7 * 16 = 49 * 10^6 * 16 = 750 * 10^6
    for (int len = 1; len <= n; len++) {
        // инициализируем нулями следующий слой динамики
        for (int num = 0; num < 4000; num++)
            for (int ans = 0; ans < 16; ans++)
                dpNext[num][ans] = 0;
        // осуществляем переходы
        for (int prevNumber = 0; prevNumber < 4000; prevNumber++)
            for (int ic = 0; ic < isz(letters); ic++) {
                int nextNumber = nextRoman[prevNumber][ic];
                int nextNumberLen = isz(roman[nextNumber]);
                for (int prevAnswer = 0; prevAnswer < 16; prevAnswer++) {
                    int nextAnswer = max(prevAnswer, nextNumberLen);
                    modAddTo(dpNext[nextNumber][nextAnswer],
                             dpCurr[prevNumber][prevAnswer]);
                }
            }
        // записываем результаты расчётов для следующего слоя в текущий слой
        dpCurr.swap(dpNext);
    }
    // подсчёт ответа по формуле:
    vector<int> cnt(16);
    for (int last = 0; last < 4000; last++)
        for (int len = 0; len < 16; len++)
            modAddTo(cnt[len], dpCurr[last][len]);
    int answ = 0;
    for (int len = 1; len < 16; len++)
        modAddTo(answ, modMul(len, cnt[len]));
    return modDiv(answ, modPow(7, n));
}

main() {
    int n;
    while (cin >> n)
        cout << solve(n) << endl;
}
