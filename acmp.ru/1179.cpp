#include <stdio.h>
#include <queue>

struct Pair {
    int number, pos;
};

bool operator<(const Pair& a, const Pair& b) {
    return a.number > b.number || (a.number == b.number && a.pos > b.pos);
}

int main() {
    int n, k; 
    scanf("%d %d", &n, &k);
    std::priority_queue<Pair> queue;
    for (int i = 0; i < k; ++i) {
        int value; scanf("%d", &value);
        queue.push(Pair{value, i});
    }
    for (int i = k; i <= n; ++i) {
        while (queue.top().pos < i-k) {
            queue.pop();
        }
        printf("%d ", queue.top().number);
        if (i < n) {
            int value; scanf("%d", &value);
            queue.push(Pair{value, i});        
        }
    }
    return 0;
}