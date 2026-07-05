#include <deque>
#include <iostream>
#include <utility>

using namespace std;

int main() {
    int q;
    cin >> q;

    deque<pair<int, int>> mins;
    int left_pos = 0;
    int right_pos = 0;

    for (int i = 0; i < q; i++) {
        char op;
        cin >> op;

        if (op == '+') {
            int x;
            cin >> x;

            while (!mins.empty() && mins.back().first >= x) {
                mins.pop_back();
            }
            mins.push_back({x, right_pos});
            right_pos++;
        } else if (op == '-') {
            if (!mins.empty() && mins.front().second == left_pos) {
                mins.pop_front();
            }
            left_pos++;
        } else {
            cout << mins.front().first << '\n';
        }
    }

    return 0;
}