#include <bits/stdc++.h>

struct Cube {
    int f, l, b, r, u, d;
    
    Cube rotate_left() const {
        return Cube{l, b, r, f, u, d};
    }
    
    Cube rotate_up() const {
        return Cube{d, l, u, r, f, b};
    }
    
    static Cube read() {
        int f, b, u, d, l, r;
        std::cin >> f >> b >> u >> d >> l >> r;
        return Cube{f, l, b, r, u, d};
    }
};

bool operator<(const Cube& a, const Cube& b) {
    if (a.f < b.f) return true; else if (a.f > b.f) return false;
    if (a.l < b.l) return true; else if (a.l > b.l) return false;
    if (a.b < b.b) return true; else if (a.b > b.b) return false;
    if (a.r < b.r) return true; else if (a.r > b.r) return false;
    if (a.u < b.u) return true; else if (a.u > b.u) return false;
    return a.d < b.d;
}

int main() {
    auto s = Cube::read();
    auto t = Cube::read();
    std::set<Cube> cubes;
    std::queue<Cube> queue;
    queue.push(s);
    cubes.insert(s);
    while (!queue.empty()) {
        auto curr = queue.front(); queue.pop();
        for (auto& next : {curr.rotate_left(), curr.rotate_up()}) {
            if (cubes.find(next) == cubes.end()) {
                cubes.insert(next);
                queue.push(next);
            }
        }
    }
    std::cout << (cubes.find(t) == cubes.end() ? "NO" : "YES") << std::endl;
    return 0;
}