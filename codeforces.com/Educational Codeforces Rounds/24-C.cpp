/*
    Problem: 818C. Sofa Thief
    
    Solution: prefix sums, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <functional>

struct Rect {
    int x1, y1, x2, y2;
    
    static Rect read() {
        int x1_, y1_, x2_, y2_;
        scanf("%d %d %d %d", &x1_, &y1_, &x2_, &y2_);
        if (x1_ > x2_) std::swap(x1_, x2_);
        if (y1_ > y2_) std::swap(y1_, y2_);
        return Rect{x1_, y1_, x2_, y2_};
    }
};

int main() {
    int n, nCols, nRows; scanf("%d %d %d", &n, &nCols, &nRows);
    std::vector<Rect> arr; std::vector<int> left, right, top, bottom;
    for (int i = 0; i < n; ++i) {
        arr.push_back(Rect::read());
        left.push_back(arr[i].x1);
        right.push_back(arr[i].x2);
        top.push_back(arr[i].y1);
        bottom.push_back(arr[i].y2);
    }
    
    std::sort(left.begin(), left.end());
    std::sort(top.begin(), top.end());
    std::sort(right.begin(), right.end(), std::greater<int>());
    std::sort(bottom.begin(), bottom.end(), std::greater<int>());
    
    // Calculate prefix sums for answer to queries:
    std::vector<int> x_pref(1+nCols+1), x_suff(1+nCols+1), y_pref(1+nRows+1), y_suff(1+nRows+1);
    
    for (int x = 1, p = 0; x <= nCols+1; ++x) {
        x_pref[x] = x_pref[x-1];
        while (p < n && left[p] == x) x_pref[x]++, p++;
    }
    
    for (int y = 1, p = 0; y <= nRows+1; ++y) {
        y_pref[y] = y_pref[y-1];
        while (p < n && top[p] == y) y_pref[y]++, p++;
    }
    
    for (int x = nCols, p = 0; x >= 0; --x) {
        x_suff[x] = x_suff[x+1];
        while (p < n && right[p] == x) x_suff[x]++, p++;
    }
    
    for (int y = nRows, p = 0; y >= 0; --y) {
        y_suff[y] = y_suff[y+1];
        while (p < n && bottom[p] == y) y_suff[y]++, p++;
    }
    
    // Find needed rect:
    int need_l, need_r, need_t, need_b, answ = -1;
    scanf("%d %d %d %d", &need_l, &need_r, &need_t, &need_b);
    for (int i = 0; i < n; ++i) {
        auto& r = arr[i];
        int curr_l = x_pref[r.x2-1] - (r.x1 < r.x2);
        int curr_r = x_suff[r.x1+1] - (r.x2 > r.x1);
        int curr_t = y_pref[r.y2-1] - (r.y1 < r.y2);
        int curr_b = y_suff[r.y1+1] - (r.y2 > r.y1);
        if (curr_l != need_l) continue;
        if (curr_r != need_r) continue;
        if (curr_t != need_t) continue;
        if (curr_b != need_b) continue;
        answ = i+1;
    }
    printf("%d", answ);
    return 0;
}