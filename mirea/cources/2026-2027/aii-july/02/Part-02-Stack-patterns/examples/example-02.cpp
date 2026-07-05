#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string s;
    cin >> s;

    vector<char> st;
    bool ok = true;

    for (char ch : s) {
        if (ch == '(') {
            st.push_back(ch);
        } else {
            if (st.empty()) {
                ok = false;
                break;
            }
            st.pop_back();
        }
    }

    if (!st.empty()) {
        ok = false;
    }

    cout << (ok ? "correct" : "incorrect") << '\n';
    return 0;
}