#include <deque>
#include <iostream>

using namespace std;

int main() {
    deque<int> d = {20, 30};

    // Deque позволяет жить на обоих концах структуры.
    d.push_front(10);
    d.push_back(40);

    cout << "front = " << d.front() << '\n';
    cout << "back = " << d.back() << '\n';

    // В C++ deque индексируется эффективно.
    cout << "middle = " << d[1] << '\n';

    d.pop_front();
    d.pop_back();

    cout << "remaining: ";
    for (int value : d) {
        cout << value << ' ';
    }
    cout << '\n';

    return 0;
}