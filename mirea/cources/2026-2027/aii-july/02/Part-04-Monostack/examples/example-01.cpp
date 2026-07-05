#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> a = {2, 1, 4, 3, 5, 2};
    vector<int> st;
    vector<int> previous_greater(a.size(), -1);

    // В олимпиадном коде монотонный стек часто пишут на vector<int>.
    for (int i = 0; i < (int)a.size(); i++) {
        while (!st.empty() && a[st.back()] <= a[i]) {
            st.pop_back();
        }

        if (!st.empty()) {
            previous_greater[i] = a[st.back()];
        }

        st.push_back(i);
    }

    cout << "previous greater values: ";
    for (int value : previous_greater) {
        cout << value << ' ';
    }
    cout << '\n';

    return 0;
}