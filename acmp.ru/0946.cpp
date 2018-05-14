#include <stdio.h>
#include <bits/stdc++.h>

int main() {
    int nQueries;
    scanf("%d", &nQueries);
    std::deque<int> deque;
    for (int q = 0; q < nQueries; ++q) {
        int type; scanf("%d", &type);
        if (type == 1) {
            int value; scanf("%d", &value);
            deque.push_front(value);
        } else if (type == 2) {
            int value; scanf("%d", &value);
            deque.push_back(value);
        } else if (type == 3) {
            printf("%d ", deque.front());
            deque.pop_front();
        } else {
            assert(type == 4);
            printf("%d ", deque.back());
            deque.pop_back();
        }
    }
    return 0;
}