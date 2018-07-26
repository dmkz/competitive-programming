/*
    Задача: 593. Башни - 2
    
    Решение: геометрия, векторное произведение, сортировка, O(n^2)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <algorithm>

typedef long long ll;

struct Vector {
    int x, y;
    
    Vector(int x_ = 0, int y_ = 0) : x(x_), y(y_) { }
    
    Vector operator-() const { 
        return Vector(-x, -y); 
    }
    
    Vector operator-(const Vector& p) const { 
        return Vector(x - p.x, y - p.y); 
    }
    
    ll cross(const Vector& p) const {
        return (ll)x * p.y - (ll)y * p.x; 
    }
};

struct Point : public Vector {
    
    int id;
    
    Point(int x_ = 0, int y_ = 0, int id_ = 0) : Vector(x_, y_), id(id_) { }
};

int main() {
    int n; scanf("%d", &n);
    std::vector<Point> pt(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &pt[i].x, &pt[i].y);
        pt[i].id = i;
    }
    std::sort(pt.begin(), pt.end(), [](const Point& a, const Point& b){return a.x < b.x;});
    std::vector<int> answ(n);
    for (int i = 0; i < n; ++i) {
        for (int j = i+1, k = i; j < n; ++j) {
            if ((pt[k] - pt[i]).cross(pt[j] - pt[i]) < 0) {
                continue;
            }
            k = j;
            answ[pt[i].id]++;
            answ[pt[j].id]++;
        }
    }
    for (auto& it : answ) {
        printf("%d\n", it);
    }
    return 0;
}