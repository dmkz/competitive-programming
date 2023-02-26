#include <bits/stdc++.h>
using namespace std;
int main() {
    string a, b;
    cin >> a >> b;
    // дополняем лидирующими нулями
    auto maxSize = max(a.size(),b.size());
    a.insert(0, string(maxSize-a.size(),'0'));
    b.insert(0, string(maxSize-b.size(),'0'));
    // сравниваем строки:
    int result = a.compare(b); // вернёт целое число
    if (result < 0) cout << "<" << endl;
    else if (result > 0) cout << ">" << endl;
    else cout << "=" << endl;
}