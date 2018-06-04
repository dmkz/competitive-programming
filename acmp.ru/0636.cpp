#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <cassert>
#include <tuple>
#include <queue>
#include <map>

struct Pair {
    int level, pos;
};

bool operator<(const Pair& a, const Pair& b) {
    return a.level < b.level || (a.level == b.level && a.pos < b.pos);
}

struct State {
    int id, local;
};

int main() {
    int nV;
    scanf("%d", &nV);
    std::map<Pair, int> id;
    std::vector<Pair> item(nV);
    std::vector<int> item_size(nV,);
    for (int i = 0; i < nV; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        item_size[a] = std::max(item_size[a], b);
        id[Pair{a,b}] = i;
        item[i] = Pair{a, b};
    }
    std::vector<int> dist(2*nV, -1);
    dist[0] = 0;
    std::queue<State> queue;
    queue.push(State{0, 0});
    while (!queue.empty()) {
        auto curr = queue.front(); queue.pop();
        int level = item[curr.id].level, pos = item[curr.id].pos;
        {
            Pair next; int id_next;
            next = Pair{level, pos-1};
            if (next.pos < 1) {
                next.pos = item_size[next.level];
            }
            id_next = id[next];
            if (dist[id_next+nV] == -1) {
                dist[id_next+nV] = dist[curr.id+curr.local*nV]+1;
                queue.push(State{id_next, 1});
            }
            next = Pair{level, pos+1};
            if (next.pos > item_size[next.level]) {
                next.pos = 1;
            }
            id_next = id[next];
            if (dist[id_next+nV] == -1) {
                dist[id_next+nV] = dist[curr.id+curr.local*nV]+1;
                queue.push(State{id_next, 1});
            }
        }
        if (!curr.local) {
            int id_next;
            id_next = curr.id-1;
            if (id_next < 0) {
                id_next += nV;
            }
            if (dist[id_next] == -1) {
                dist[id_next] = dist[curr.id]+1;
                queue.push(State{id_next,0});
            }
            id_next = curr.id+1;
            if (id_next >= nV) {
                id_next -= nV;
            }
            if (dist[id_next] == -1) {
                dist[id_next] = dist[curr.id]+1;
                queue.push(State{id_next,0});
            }
        }
    }
    for (int i = 0; i < nV; ++i) {
        printf("%d ", std::min(dist[i], dist[i+nV]));
    }
    return 0;
}