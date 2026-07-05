#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> a = {5, 2, 4, 1, 3};
    vector<int> st;
    vector<int> next_smaller(a.size(), -1);

    // Идём справа налево и ищем ближайший меньший элемент справа.
    for (int i = (int)a.size() - 1; i >= 0; i--) {
        while (!st.empty() && a[st.back()] >= a[i]) {
            st.pop_back();
        }

        if (!st.empty()) {
            next_smaller[i] = a[st.back()];
        }

        st.push_back(i);
    }

    cout << "next smaller values: ";
    for (int value : next_smaller) {
        cout << value << ' ';
    }
    cout << '\n';

    return 0;
}