// Задача: B, Вердикт: OK, Время: 2ms, Память: 844.00Kb
#include <bits/stdc++.h>
using namespace std;
main() {
    int birthYear;
    cin >> birthYear;
    int joinYear;
    cin >> joinYear;
    int numSems;
    cin >> numSems;
    int numFinals;
    cin >> numFinals;
    int numRegionals;
    cin >> numRegionals;
    // определяем ответ
    string answer = "+"; // изначально считаем, что участие разрешено, далее проверки
    if (numFinals >= 2) {
        answer = "-"; // участие запрещено
    } else if (numRegionals >= 6) {
        answer = "-"; // участие запрещено
    } else if (numRegionals == 5 || (birthYear < 2002 && joinYear < 2021)) {
        // применяется правило 5
        if (numSems >= 9) // участие запрещено
            answer = "-";
        else // участие под вопросом
            answer = "?";
    }
    cout << answer << endl;
}
