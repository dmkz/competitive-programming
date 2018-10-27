/*
    Problem: 350C. Bombs
    
    Solution: geometry, constructive, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

typedef long long ll;

struct Point {
    ll x, y;
    
    static Point read() {
        ll x_, y_;
        std::cin >> x_ >> y_;
        return Point{x_, y_};
    }
    
    ll norm() const {
        return std::abs(x) + std::abs(y);
    }
};

bool operator<(const Point& a, const Point& b) {
    return a.norm() < b.norm() || (a.norm() < b.norm() && (a.x < b.x || (a.x == b.x && a.y < b.y)));
}

struct Query {
    int type; ll count; char side;
    
    Query(int type_ = 0, ll count_ = 0, char side_ = '?')
        : type(type_), count(count_), side(side_) { }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int n; std::cin >> n;
    std::vector<Point> pt(n);
    for (auto& it : pt) {
        it = Point::read();
    }
    std::sort(pt.begin(), pt.end());
    std::vector<Query> answer;
    for (auto& it : pt) {
        if (it.x < 0) {
            answer.push_back(Query(1, -it.x, 'L'));
        } else if (it.x > 0) {
            answer.push_back(Query(1, it.x, 'R'));
        }
        if (it.y < 0) {
            answer.push_back(Query(1, -it.y, 'D'));
        } else if (it.y > 0) {
            answer.push_back(Query(1, it.y, 'U'));
        }
        answer.push_back(Query(2));
        if (it.y < 0) {
            answer.push_back(Query(1, -it.y, 'U'));
        } else if (it.y > 0) {
            answer.push_back(Query(1, it.y, 'D'));
        }
        if (it.x < 0) {
            answer.push_back(Query(1, -it.x, 'R'));
        } else if (it.x > 0) {
            answer.push_back(Query(1, it.x, 'L'));
        }
        answer.push_back(Query(3));
    }
    std::cout << answer.size() << "\n";
    for (auto& it : answer) {
        if (it.type == 1) {
            std::cout << it.type << ' ' << it.count << ' ' << it.side << '\n';
        } else {
            std::cout << it.type << '\n';
        }
    }
    return 0;
}