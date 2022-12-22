#include <bits/stdc++.h>
#define all(x) std::begin(x), std::end(x)
#define isz(x) (int)std::size(x)
using pii = std::pair<int,int>;
using vpii = std::vector<pii>;
using vi = std::vector<int>;
using ll = long long;
int lowpos(const auto &x, const auto &y) {
    return int(std::lower_bound(all(x),y)-x.begin());
}
void reuniq(auto &x) {
    x.erase(std::unique(all(x)), x.end());
}
void part1() {
    std::string s;
    const int yt = 2000000;
    std::map<int, vi> beacons;
    std::set<int> banned;
    while(std::getline(std::cin, s)) {
        int x, y, xb, yb;
        sscanf(s.c_str(), "Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d", &x, &y, &xb, &yb);
        int dist = std::abs(x - xb) + std::abs(y - yb);
        int deltaY = std::abs(y - yt);
        if (deltaY > dist) continue;
        int deltaX = dist - deltaY;
        for (int xx = x - deltaX; xx <= x + deltaX; xx++) {
            banned.insert(xx);
        }
        beacons[yb].push_back(xb);
    }
    for (int xb : beacons[yt])
        banned.erase(xb);
    std::cout << isz(banned) << std::endl;
}
const int MAX = 4000000;
const int yMin = 0, yMax = MAX;
const int xMin = 0, xMax = MAX;
int solveY(const vpii& banned, const vi & beacons) {
    vi coords{xMin, xMax};
    for (auto [x1,x2] : banned)
        coords.insert(coords.end(), {x1-1,x1,x1+1,x2-1,x2,x2+1});
    for (auto x : beacons)
        coords.push_back(x);
    std::sort(all(coords));
    reuniq(coords);
    vi add(isz(coords));
    auto add_on_segment = [&](int L, int R, int delta) {
        int iL = lowpos(coords, L);
        int iR = lowpos(coords, R);
        add[iL]+=delta;
        add[iR+1]-=delta;
    };
    for (auto [x1,x2] : banned)
        add_on_segment(x1,x2,1);
    for (int i = 1; i < isz(add); i++)
        add[i] += add[i-1];
    for (int i = 0; i < isz(add); i++) {
        const int x = coords[i];
        if (xMin <= x && x <= xMax && add[i] == 0)
            return x;
    }
    return -1;
}
int main() {    
    std::string s;
    std::map<int, vi> beacons;
    std::map<int, vpii> banned;
    int idLine = 0;
    while(std::getline(std::cin, s)) {
        int x, y, xb, yb;
        sscanf(s.c_str(), "Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d", &x, &y, &xb, &yb);
        int dist = std::abs(x - xb) + std::abs(y - yb);
        for (int yt = yMin; yt <= yMax; yt++) {
            int deltaY = std::abs(y - yt);
            if (deltaY > dist) continue;
            int deltaX = dist - deltaY;
            banned[yt].push_back({x - deltaX, x + deltaX});
        }
        beacons[yb].push_back(xb);
        std::cout << "line " << ++idLine << " is readed!" << std::endl;
    }
    ll answ{-1};
    for (int y = yMin; y <= yMax; y++) {
        int x = solveY(banned[y], beacons[y]);
        if (x != -1) {
            answ = 4000000LL * x + y;
            break;
        }
        if (y % 1024 == 0) {
            std::cout << "y " << y << " is processed!" << std::endl;
        }
    }
    assert(answ != -1);
    std::cout << answ << std::endl;
}