/*
    Problem: 845E. Fire in the City
    
    Solution: binary search, geometry, sorting, events, O(log(n) * k^2 * log(k))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cassert>
#include <functional>

struct Point {
    int x, y;
};

struct Rect {
    int x_min, x_max, y_min, y_max;
};

const int OPEN = 0, CLOSE = 2, CHECK = 1;

struct Event {
    int pos, type;
};

inline bool operator<(const Event& a, const Event& b) {
    return a.pos < b.pos || (a.pos == b.pos && a.type < b.type);
}

int main() {
    // Input points:
    int NX, NY, k; scanf("%d %d %d", &NX, &NY, &k);
    std::vector<Point> pt(k);
    for (auto& p : pt) {
        scanf("%d %d", &p.x, &p.y);
    }
    // Function for answer to one query with fixed time:
    std::function<bool(int)> can = [&](int time) {
        // Create array of rects with size 2*time+1 and centres in points pt[1..k]:
        std::vector<Rect> rects;
        std::vector<int> x{1,NX}; // `x` which we need to check
        for (auto& p : pt) {
            int x1 = std::max( 1, p.x-time);
            int x2 = std::min(NX, p.x+time);
            int y1 = std::max( 1, p.y-time);
            int y2 = std::min(NY, p.y+time);
            rects.push_back(Rect{x1,x2,y1,y2});
            x.push_back(x1);
            x.push_back(x2);
            x.push_back(std::max(1, x1-1));
            x.push_back(std::min(NX, x2+1));
        }
        std::sort(x.begin(), x.end());
        x.erase(std::unique(x.begin(), x.end()), x.end());
        // Check each `x`-coord and solve one-dimensional segments intersection problem:
        int x_min = NX, x_max = 1, y_min = NY, y_max = 1;
        for (int i = 0; i < (int)x.size(); ++i) {
            // Create and sort events of types "OPEN", "CHECK" and "CLOSE" on line `x` = x[i]:
            std::vector<Event> events;
            events.push_back(Event{ 1, CHECK});
            events.push_back(Event{NY, CHECK});
            for (auto& r : rects) {
                if (r.x_min <= x[i] && x[i] <= r.x_max) { 
                    // Add events for each rect which contains `x` coord:
                    events.push_back(Event{r.y_min,  OPEN});
                    events.push_back(Event{r.y_max, CLOSE});
                    events.push_back(Event{std::max( 1, r.y_min-1), CHECK});
                    events.push_back(Event{std::min(NY, r.y_max+1), CHECK});
                }
            }
            std::sort(events.begin(), events.end());
            // Find segments with balance = 0 and update borders:
            int balance = 0;
            for (auto& e : events) {
                if (e.type == OPEN) {
                    balance++;
                } else if (e.type == CLOSE) {
                    balance--;
                } else if (e.type == CHECK) {
                    if (balance == 0) {
                        x_min = std::min(x_min, x[i]);
                        x_max = std::max(x_max, x[i]);
                        y_min = std::min(y_min, e.pos);
                        y_max = std::max(y_max, e.pos);
                    }
                }
            }
        }
        int max = std::max(x_max-x_min+1, y_max-y_min+1);
        return max <= 2*time+1;
    };
    // Binary search on time:
    int low = -1, high = std::max(NX, NY)+1;
    while (high - low > 1) {
        int mid = (low + high) / 2;
        if (can(mid)) {
            high = mid;
        } else low = mid;
    }
    printf("%d", high);
    return 0;
}