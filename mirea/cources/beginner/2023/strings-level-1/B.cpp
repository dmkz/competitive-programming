#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; cin >> n;
    string s; cin >> s;
    // фактически, нужно разбить строку на подстроки, используя
    // '0' как разделитель, то есть сделать split по символу '0'
    // В C++ нет split, придётся самим
    s += '0'; // добавим '0' в конец так, чтобы после каждого блока шёл 0
    int currBlockLen = 0;
    for (int i = 0; i <= n; i++) {
        if (s[i] == '0') {
            cout << currBlockLen;
            currBlockLen = 0;
        } else {
            currBlockLen++;
        }
    }
}