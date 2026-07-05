#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> st;

    // В олимпиадном коде стек часто пишут на vector.
    st.push_back(10);
    st.push_back(20);
    st.push_back(30);

    cout << "top = " << st.back() << '\n';
    cout << "size = " << st.size() << '\n';

    // Можно посмотреть и на верхушку, и на более ранние элементы.
    cout << "second element = " << st[1] << '\n';

    st.pop_back();
    cout << "top after pop = " << st.back() << '\n';
    cout << "empty = " << (st.empty() ? "yes" : "no") << '\n';

    return 0;
}