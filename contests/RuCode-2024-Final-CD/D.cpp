// 123456789012345
// ABCDEFGHIJKLMNO
// он будет называть всё время чётные буквы B, D, F
// мы можем называть нечётные буквы и k чётных букв с конца
#include <bits/stdc++.h>
using namespace std;
main() {
    int n, k; cin >> n >> k;
    int numLetters = n;
    string alice, bob;
    for (int i = 0; i < n; i++)
        if (i % 2 == 0)
            alice += char('A' + i);
        else
            bob += char('A' + i);
    if (k > 0 && n % 2 == 1)
        alice.pop_back();
    while (k --> 0) {
        int i = (int)bob.size()-1;
        swap(alice[i], bob[i]);
        bob.pop_back();
    }
    // n = 5, k = 2
    // ABCDE
    set<char> letters;
    auto findLetter = [&](){
        while (alice.size()) {
            char c = alice.front();
            alice.erase(alice.begin());
            if (letters.count(c) == 0) {
                return c;
            }
        }
        for (int i = 0; i < numLetters; i++) {
            char c = char('A' + i);
            if (letters.count(c) == 0)
                return c;
        }
        return '?';
    };
    while (n > 0) {
        char c = findLetter();
        assert(c != '?');
        cout << c << endl;
        letters.insert(c);
        n--;
        if (n > 0) {
            cin >> c;
            letters.insert(c);
            n--;
        }
    }
}
