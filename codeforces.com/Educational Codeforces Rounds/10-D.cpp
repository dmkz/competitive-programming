/*
    Problem: 652D. Nested Segments
    
    Solution: Sqrt-Decomposition, sorting, events, stack, O(n sqrt(n))
    
    Author: Dmitry Kozyrev, https://github.com/dmkz , dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cassert>
#include <iostream>

struct SqrtDecomposition {
    std::vector<int> arr, extra;
    
    static const int gsize = 256;
    
    SqrtDecomposition(int size, int element = 0) { 
        arr.assign(size, element);
        extra.assign((size+gsize-1)/gsize,0);
    }
    
    void add(int l, int r, int v) {
        const int gl = l / gsize;
        const int gr = r / gsize;
        if (gl == gr) {
            for (int i = l; i <= r; ++i) {
                arr[i] += v;
            }
        } else {
            for (int i = l, after = (gl+1)*gsize; i < after; ++i) {
                arr[i] += v;
            }
            for (int g = gl + 1; g < gr; ++g) {
                extra[g] += v;
            }
            for (int i = gr*gsize; i <= r; ++i) {
                arr[i] += v;
            }
        }
    }
    
    inline int get(int pos) const {
        return arr.at(pos) + extra.at(pos / gsize);
    }
    
    void set(int pos, int value) {
        const int gp = pos / gsize;
        const int after = std::min(gp * gsize, (int)arr.size());
        for (int i = gp * gsize; i < after; ++i) {
            arr[i] += extra[gp];
        }
        extra[gp] = 0;
        arr[pos] = value;
    }
};

const int OPEN = 0;
const int CLOSE = 1;

struct Event {
    int pos, id, type;
};


int main() {
    int n;
    scanf("%d", &n);
    
    // Creating events to open or close a segment:
    std::vector<Event> events;
    
    for (int i = 0; i < n; ++i) {
        int l, r;
        scanf("%d %d", &l, &r);
        events.push_back(Event{l, i,  OPEN});
        events.push_back(Event{r, i, CLOSE});
    }
    
    // Sorting all events:
    std::sort(events.begin(), events.end(), [](const Event& a, const Event& b) {
        assert(a.pos != b.pos);
        return a.pos < b.pos;
    });
    
    // Create sqrt-decomposition over segments:
    SqrtDecomposition sd(n);
    
    std::vector<int> pos(n, -1);
    
    std::vector<int> answ(n);
    
    int size = 0;    
    for (auto & e : events) {
        if (e.type == OPEN) { // Push to stack
            pos[e.id] = size++;
        } else {
            int value = sd.get(pos[e.id]);
            answ[e.id] = value;
            sd.add(0, pos[e.id], 1); // Increase all answers for opened segments
        }
    }
    
    for (auto it : answ) {
        printf("%d\n", it);
    }
    
    return 0;
}