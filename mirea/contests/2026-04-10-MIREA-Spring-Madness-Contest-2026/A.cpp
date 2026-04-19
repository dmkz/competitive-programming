// обработка строк, getline, O(n)
#include <bits/stdc++.h>
using namespace std;
main() {
    int n; cin >> n;
    string s; getline(cin, s); // дочитываем первую строку до конца
    while (n --> 0) {
        getline(cin, s);
        bool open = true;
        for (int i = 0; i < (int)s.size(); i++)
            if (s[i] == '|') {
                s[i] = (open ? '[' : ']');
                open = !open;
            }
        cout << s << '\n';
    }
}