#pragma GCC diagnostic ignored "-Wunused-result"

#include <stdio.h>
#include <bits/stdc++.h>

int get_time() {
    int h, m, s; scanf("%d:%d:%d", &h, &m, &s);
    return s + 60 * (m + 60 * h);
}

void put_time(int s) {
    int h = s / 3600 % 24;
    int m = s / 60 % 60;
    s %= 60;
    printf("%02d:%02d:%02d", h, m, s);
}

struct Record {
    int id, time, dur;
};

int main() {
    int n, qSize; scanf("%d %d", &n, &qSize);
    std::deque<Record> deque;
    std::vector<std::pair<int, int>> answ(n, {-1, -1});
    int global_time = 0;
    for (int i = 0; i < n; ++i) {
        int time = std::max(get_time(), global_time), dur; scanf("%d", &dur);
        deque.push_back(Record{i, time, dur});
        if ((int)deque.size() == qSize) {
            while (!deque.empty()) {
                auto curr = deque.front(); deque.pop_front();
                if (answ[curr.id].first == -1) {
                    answ[curr.id].first = time;
                }
                int dec = std::min(10, curr.dur);
                curr.dur -= dec;
                if (curr.dur == 0) {
                    answ[curr.id].second = time + dec;
                } else {
                    deque.push_back(curr);
                }
                time += dec;
            }
            global_time = time;
        }
    }
    for (auto& it : answ) {
        put_time(it.first); printf(" "); put_time(it.second); printf("\n");
    }
    return 0;
}