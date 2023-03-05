#include <bits/stdc++.h>
using namespace std;
int main() {
    // прочитаем все даты и сохраним в вектор в формате:
    // год.месяц.день час:минута:секунда
    int n; scanf("%d", &n);
    vector<string> times;
    while (n --> 0) {
        // читаем из ввода:
        int seconds, minute, hour, day, month, year;
        scanf("%d:%d:%d %d.%d.%d",
              &seconds, &minute, &hour, &day, &month, &year);
        // выводим в строку:
        char result[100];
        sprintf(result, "%04d.%02d.%02d %02d:%02d:%02d",
                year, month, day, hour, minute, seconds);
        // заносим строку в вектор:
        times.push_back(result);
    }
    // сортируем даты:
    sort(times.begin(), times.end());
    // выводим их в изначальном формате:
    for (const auto &s : times) {
        // читаем из строки:
        int seconds, minute, hour, day, month, year;
        sscanf(s.c_str(), "%04d.%02d.%02d %02d:%02d:%02d",
                        &year, &month, &day, &hour, &minute, &seconds);
        // печатаем в вывод:
        printf("%02d:%02d:%02d %02d.%02d.%04d\n",
               seconds, minute, hour, day, month, year);
    }
}