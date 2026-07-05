#include <iostream>
#include <queue>

using namespace std;

int main() {
    queue<int> q;

    // Очередь удобна, когда удаление всегда происходит из начала.
    q.push(10);
    q.push(20);
    q.push(30);

    cout << "front = " << q.front() << '\n';
    q.pop();
    cout << "front after pop = " << q.front() << '\n';
    cout << "back = " << q.back() << '\n';

    return 0;
}