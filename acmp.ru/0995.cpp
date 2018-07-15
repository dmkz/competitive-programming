/*
    "Голова на плечах": сортировка по полярному углу, дерево отрезков, O(n log(n))
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <string>

struct SegmentTree {
    
    const int size;
    
    std::vector<int> data;
    
    void build(int v, int l, int r, const std::vector<int>& arr) {
        if (l == r) {
            data[v] = arr[l];
        } else {
            int m = (l + r) / 2;
            build(2*v+1,   l, m, arr);
            build(2*v+2, m+1, r, arr);
            data[v] = data[2*v+1]+data[2*v+2];
        }
    }
    
    void set(int v, int l, int r, int pos, int value) {
        if (l == r) {
            data[v] = value;
        } else {
            int m = (l + r) / 2;
            if (pos <= m) {
                set(2*v+1,   l, m, pos, value);
            } else {
                set(2*v+2, m+1, r, pos, value);
            }
            data[v] = data[2*v+1]+data[2*v+2];
        }
    }
    
    void set(int pos, int value) {
        set(0, 0, size-1, pos, value);
    }
    
    int get(int v, int l, int r, int ql, int qr) const {
        if (l == ql && r == qr) {
            return data[v];
        } else {
            int m = (l + r) / 2;
            if (qr <= m) {
                return get(2*v+1,   l, m, ql, qr);
            } else if (ql > m) {
                return get(2*v+2, m+1, r, ql, qr);
            } else {
                return get(2*v+1,   l, m, ql, m) + get(2*v+2, m+1, r, m+1, qr);
            }
        }
    }
    
    int get(int left, int right) const {
        return get(0, 0, size-1, left, right);
    }
    
    SegmentTree(const std::vector<int>& arr) : size((int)arr.size()) {
        int pow = 1;
        while (pow < size) pow *= 2;
        data.resize(2 * pow);
        build(0, 0, size-1, arr);
    }
};

typedef double Real;

const Real PI = std::acos(-1.0L);

struct Point {
    Real x, y; int id;
    
    inline Point rotate(Real angle) const {
        return Point{
            std::cos(angle) * x - std::sin(angle) * y,
            std::sin(angle) * x + std::cos(angle) * y,
            id
        };
    }
    
    inline Real angle() const {
        return std::atan2(y, x);
    }
};

int main() {    
    int n; scanf("%*d %*d %d", &n);
    if (n == 0) {
        printf("0");
        return 0;
    }
    std::vector<Point> circle, line;
    circle.reserve(n);
    line.reserve(n);
    for (int i = 0; i < n; ++i) {
        double x1, y1, x2, y2;
        scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
        circle.push_back(Point{Real(x1),Real(y1),i});
        line.push_back(Point{Real(x2),Real(y2),i});
    }
    
    std::sort(line.begin(), line.end(), [](const Point& a, const Point& b) {
        assert(a.x != b.x);
        return a.x < b.x;
    });
    
    std::sort(circle.begin(), circle.end(), [](const Point& a, const Point& b) {
        return a.rotate(PI/2).angle() < b.rotate(PI/2).angle();
    });
    
    int pos = 0;
    std::vector<int> f(n);
    for (auto& p : line) {
        f[p.id] = pos++;
    }
    
    SegmentTree st(std::vector<int>(n,0));
    
    long long answ = 0;
    for (auto& p : circle) {
        answ += st.get(f[p.id], n-1);
        st.set(f[p.id],1);
    }
    printf("%s", std::to_string(answ).c_str());
    return 0;
}