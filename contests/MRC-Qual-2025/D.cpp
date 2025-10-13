// Задача: D, Вердикт: OK, Время: 2ms, Память: 808.00Kb
#include <bits/stdc++.h>
using namespace std;
main() {
    // читаем данные: сразу в вещественных числах
    double downloadTime, speed, downloaded;
    cin >> downloadTime >> speed >> downloaded;
    // проще всего посчитать длину дуги: 360 умножить на процент скачивания
    double circleLength = 360.0 * downloaded / 100.0;
    // считаем стартовую позицию: время скачивания умножить на процент скачивания
    // умножить на скорость вращения - получим количество пройденных градусов
    // так как могло быть сделано несколько полных оборотов, то нужно вычесть
    // все полные обороты. Таким образом мы найдём текущее положение на окружности
    double path = speed * downloadTime * downloaded / 100.0;
    double fullCircles = floor(path / 360.0);
    double start = path - fullCircles * 360.0;
    double finish = start + circleLength;
    if (finish >= 360.0)
        finish -= 360.0;
    // настраиваем формат вывода и выводим ответ:
    cout << fixed << setprecision(4); // выводить в фиксированной форме с 4-мя знаками после запятой
    cout << start << ' ' << finish << '\n';
}
