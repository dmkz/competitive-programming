// Задача: G, Вердикт: OK, Время: 0.527s, Память: 198.64Mb

// Длина лучшего ответа не превосходит sqrt(n), потому что всегда можно разбить
// нашу строку на последовательность из чисел длины 1, 2, 3, 4, ..., sqrt(n).
// Переберём длину ответа и для каждой длины проверим, можно ли её достичь
// Чтобы не перебирать одни и те же варианты несколько раз, используем технику
// динамического программирования с запоминанием, какие варианты мы уже перебрали

#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
// сравнение подстрок s[a...b] > s[c...d] как чисел
bool isGreater(const string &s, int a, int b, int c, int d) {
    if (b - a > d - c) return true;
    if (b - a < d - c) return false;
    return memcmp(s.c_str() + a, s.c_str() + c, d - c + 1) > 0;
}
string solve(const string &s) {
    // находим ограничение на максимальный ответ
    const int n = (int)s.size();
    int maxAnswer = 1;
    while (maxAnswer * (maxAnswer+1) / 2 <= n)
        maxAnswer++;
    // выделяем память под хранение результатов вычисления динамики
    vector canLeft(n+1, vector<bool>(maxAnswer+1, false));
    vector canRight(n+1, vector<bool>(maxAnswer+1, false));
    vector canLeftSum(n+1, vector<int16_t>(maxAnswer+1, 0));
    vector canRightSum(n+1, vector<int16_t>(maxAnswer+1, 0));
    for (int len = 1; len <= n; len++) {
        for (int last = 1; last <= min(len, maxAnswer); last++) {
            // можно ли выбрать возрастающую последовательность на префиксе
            // s[0 ... len-1] так, чтобы последнее число имело длину last?
            
            // можем, если можем для префикса s[0 ... len - last] выбрать
            // подпоследоследовательность, оканчивающуюся на число длины < last:
            // проверяем сначала меньшие предыдущие длины:
            bool ok = (canLeftSum[len - last][last - 1] > 0);
            if (ok) {
                canLeft[len][last] = true;
            } else {
                // иначе единственный вариант - нужно проверить такую же длину
                // для этого сравниваем подстроки лексикографически. справа должна
                // быть бОльшая
                int pos = len - 2 * last;
                if (pos >= 0 && canLeft[len - last][last] &&
                    isGreater(s, pos + last, len - 1, pos, pos + last - 1))
                {
                    canLeft[len][last] = true;
                }
            }
        }
        // крайний случай когда берём весь префикс как одно число:
        if (len <= maxAnswer && !canLeft[len][len])
            canLeft[len][len] = true;
        // предподсчитываем префикс-суммы для текущего столбца на будущее:
        canLeftSum[len][0] = canLeft[len][0];
        for (int i = 1; i <= maxAnswer; i++)
            canLeftSum[len][i] = canLeftSum[len][i-1] + canLeft[len][i];
    }
    // аналогично, но теперь справа-налево
    for (int len = 1; len <= n; len++) {
        for (int last = 1; last <= min(len, maxAnswer); last++) {
            // можно ли выбрать убывающую последовательность на суффиксе
            // s[n-len ... n-1] так, чтобы самое левое число имело длину last?
            
            // можем, если можем для суффикса s[n-len+last ... n-1] выбрать
            // подпоследоследовательность, самое левое число которой имеет
            // длину < last:
            bool ok = (canRightSum[len - last][last - 1] > 0);
            if (ok) {
                canRight[len][last] = true;
            } else {
                // иначе нужно проверять такую же длину
                // число слева должно быть больше чем число справа
                int pos = n - len;
                if (pos + 2 * last <= n && canRight[len - last][last] &&
                    isGreater(s, pos, pos + last - 1, pos + last, pos + 2 * last - 1))
                {
                    canRight[len][last] = true;
                }
            }
        }
        // крайний случай, когда мы берём весь суффикс как число
        if (len <= maxAnswer && !canRight[len][len])
            canRight[len][len] = true;
        // предподсчитываем префикс-суммы для текущего столбца на будущее:
        canRightSum[len][0] = canRight[len][0];
        for (int i = 1; i <= maxAnswer; i++)
            canRightSum[len][i] = canRightSum[len][i-1] + canRight[len][i];
    }
    // выбираем лучший ответ:
    auto answer = make_pair(n, s);
    for (int prefLen = 1; prefLen <= maxAnswer; prefLen++)
        if (canRight[n][prefLen]) { // лучший префикс
            answer = min(answer, make_pair(prefLen, s.substr(0, prefLen)));
            break;
        }
    for (int suffLen = 1; suffLen <= maxAnswer; suffLen++)
        if (canLeft[n][suffLen]) { // лучший суффикс
            answer = min(answer, make_pair(suffLen, s.substr(n - suffLen, suffLen)));
            break;
        }
    return answer.second; // возвращаем ответ
}
main() {
    string s;
    cin >> s;
    cout << solve(s) << endl;
}
