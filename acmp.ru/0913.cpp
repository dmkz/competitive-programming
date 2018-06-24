#include <stdio.h>
#include <vector>
#include <cassert>
#include <algorithm>
#include <functional>

struct Segment {
    int d, l, h;
    
    static Segment read() {
        int d, l, h;
        scanf("%d %d %d", &d, &l, &h);
        return Segment{d, l, h};
    }
};

int main() {
    int n, limit;
    scanf("%d %d", &n, &limit);
    
    std::vector<int> possible_speed{limit};
    
    std::vector<Segment> s;
    for (int i = 0; i < n; ++i) {
        s.push_back(Segment::read());
        if (s.back().l <= limit) {
            possible_speed.push_back(s.back().l);
        }
        if (s.back().l+1 <= limit) {
            possible_speed.push_back(s.back().l+1);
        }
    }    
    
    std::sort(possible_speed.begin(), possible_speed.end(), std::greater<int>());
    
    double best = 1e9; int answ = -1;
    for (int speed : possible_speed) {
        double sum = 0;
        for (auto& it : s) {
            if (speed <= it.l) {
                sum += 1.0 * it.d / speed;
            } else {
                sum += 1.0 * it.d / speed + it.h;
            }
        }
        if (sum < best) {
            answ = speed;
            best = sum;
        }
    }
    assert(answ != -1);
    printf("%d", answ);
    return 0;
}