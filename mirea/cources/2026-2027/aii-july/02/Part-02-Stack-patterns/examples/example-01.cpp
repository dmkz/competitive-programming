#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string s = "ABBACA";
    vector<char> st;

    // Держим в стеке уже сокращённую часть строки.
    for (char ch : s) {
        if (!st.empty() && st.back() == ch) {
            st.pop_back();
        } else {
            st.push_back(ch);
        }
    }

    cout << "result: ";
    for (char ch : st) {
        cout << ch;
    }
    cout << '\n';

    return 0;
}