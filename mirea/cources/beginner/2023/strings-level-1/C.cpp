#include <bits/stdc++.h>
using namespace std;
int main() {
    string s; cin >> s;
    // сперва заменим все разделители на запятую и добавим одну запятую в конец
    s += ',';
    for (int i = 0; i < (int)s.size(); i++)
        if (s[i] == ';')
            s[i] = ',';
    // теперь нужно сделать split по запятым, как делали в задаче B
    string currBlock; // изначально блок пуст
    string a = "\"", b = "\""; // изначально a и b состоят только из кавычек
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == ',') {
            // обработать блок. Является ли целым числом без лидирующих нулей?
            bool isNumber = !currBlock.empty();
            // все символы должны быть цифры
            for (auto c : currBlock)
                isNumber &= (isdigit(c) != 0);
            // первый символ у двузначных и больше не должен быть нулём:
            if (currBlock.size() > 1u) 
                isNumber &= (currBlock[0] != '0');
            // добавить подстроку в a или b
            if (isNumber) (a += currBlock) += ',';
            else (b += currBlock) += ',';
            // подготовиться к обработке следующего блока
            currBlock = "";
        } else {
            currBlock += s[i];
        }
    }
    // в конце должна стоять либо кавычка, либо ','. Заменяем на кавычку
    a.back() = '"';
    b.back() = '"';
    // особый случай, когда не было ни одного числа или не числа:
    if (a.size() == 1u) a = "-";
    if (b.size() == 1u) b = "-";
    // выводим ответ:
    cout << a << '\n' << b << '\n';
}