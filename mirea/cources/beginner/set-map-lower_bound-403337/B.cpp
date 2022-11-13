#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // будем хранить оригинальное имя для каждого нового имени
    // и список активных имён
    int n; cin >> n;
    map<string, string> originalName;
    set<string> actualNames;
    while(n--) {
        string oldName, newName;
        cin >> oldName >> newName;
        // произошла замена имени:
        actualNames.erase(oldName);  // старое выкидываем
        actualNames.insert(newName); // новое оставляем
        // инициализируем, если oldName ещё не было
        if(!originalName.count(oldName))
            originalName[oldName] = oldName;
        // сохраняем оригинальное имя для нового имени
        originalName[newName] = originalName[oldName];
    }
    // выводим ответ
    cout << actualNames.size() << '\n';
    for (const auto &name : actualNames)
        cout << originalName[name] << ' ' << name << '\n';
}