#pragma GCC diagnostic ignored "-Wunused-result"

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cassert>

struct Rect {
    int x_min, y_min, x_max, y_max;
    
    Rect(int x_min=0, int y_min=0, int x_max=0, int y_max=0) 
        : x_min(x_min)
        , y_min(y_min)
        , x_max(x_max)
        , y_max(y_max)
    { }
                
    static Rect read() {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        return Rect(
            std::min(x1, x2), 
            std::min(y1, y2), 
            std::max(x1, x2), 
            std::max(y1, y2)
        );
    }
    
    Rect intersect(const Rect& r) const {
        return Rect(
            std::max(x_min, r.x_min), 
            std::max(y_min, r.y_min), 
            std::min(x_max, r.x_max), 
            std::min(y_max, r.y_max)
        );
    }
    
    bool correct() const {
        return x_max >= x_min && y_max >= y_min;
    }
                
    int square() const {
        return (x_max - x_min) * (y_max - y_min);
    }
};

int main() {
    int n; scanf("%d", &n); 
    
    std::vector<Rect> rects(n);
    for (auto& it : rects) {
        it = Rect::read();
    }
    
    Rect cur = Rect::read();
    
    int s = 0;
    for (const auto& it : rects) {
        auto temp = cur.intersect(it);
        s += temp.correct() ? temp.square() : 0;
    }
    printf("%d\n", s);
    return 0;
}