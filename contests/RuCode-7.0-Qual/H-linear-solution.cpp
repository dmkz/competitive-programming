#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
void remin(auto &x, const auto &y) { if (x > y) x = y; }
void remax(auto &x, const auto &y) { if (x < y) x = y; }
using ll = long long;
using ld = long double;
using pii = std::pair<int,int>;
using vi = std::vector<int>;
using vpii = std::vector<pii>;
using vvpii = std::vector<vpii>;
using tiii = std::tuple<int,int,int>;
using vtiii = std::vector<tiii>;
#ifndef __GEOMA_HPP__
#define __GEOMA_HPP__
namespace algos {
namespace geoma {

template<typename A, typename B>
inline std::pair<A,B> operator-(const std::pair<A,B> &a, const std::pair<A,B> &b) {
    return std::pair<A,B>(a.first - b.first, a.second - b.second);
}
template<typename A, typename B>
inline std::pair<A,B> operator+(const std::pair<A,B> &a, const std::pair<A,B> &b) {
    return std::pair<A,B>(a.first + b.first, a.second + b.second);
}

template<typename T, typename A, typename B>
inline T cross(const std::pair<A,B> &a, const std::pair<A,B> &b) {
    return T(a.first) * b.second - T(a.second) * b.first;
}

template<typename T, typename A, typename B>
inline T doubleSquare(const std::pair<A,B> &a, const std::pair<A,B> &b, const std::pair<A,B> &c) {
    T res = cross<T>(a-b, c-b);
    if (res < 0)
        res = -res;
    return res;
}

template<typename T, typename A, typename B>
inline T dist2(const std::pair<A,B> &a) {
    return T(a.first)*a.first + T(a.second)*a.second;
}

template<typename T, typename A, typename B>
inline T dist2(const std::pair<A, B> &a, const std::pair<A, B> &b) {
    return dist2<T>(a-b);
}

inline ll orientedSquare(const std::vector<pii> &points) {
    ll res = cross<ll>(points.back(), points.front());
    for (int i = 0; i + 1 < isz(points); i++)
        res += cross<ll>(points[i], points[i+1]);
    return res;
}

inline vpii readPolygon() {
    int n;
    vpii points;
    std::cin >> n;
    points.resize(n);
    for (auto &[x,y] : points)
        std::cin >> x >> y;
    return points;
}

inline void moveToPositive(vpii &points) {
    int minX = INT_MAX, minY = INT_MAX;
    for (auto &[x,y] : points) {
        remin(minX, x);
        remin(minY, y);
    }
    if (minX % 2 != 0) minX--;
    if (minY % 2 != 0) minY--;
    for (auto &[x,y] : points)
        x -= minX, y -= minY;
}

inline void transpose(vpii &points) {
    for (auto &[x,y] : points)
        std::swap(x, y);
}

inline void makeCounterClockwise(vpii &points) {
    ll sq = orientedSquare(points);
    if (sq < 0) std::reverse(all(points));
}

inline int sign(auto x) { return x < 0 ? -1 : (x > 0 ? +1 : 0); }

const int LEFT = -1, RIGHT = +1;

inline int rotation(pii first, pii mid, pii last) {
// > 0 --> right
// < 0 --> left
    return sign(cross<ll>(first-mid,last-mid));
}
} // geoma
} // algos
#endif // __GEOMA_HPP__
using namespace algos::geoma;

pii pickPointOutside(pii A, pii B) {
    pii C1(A.first, B.second);
    pii C2(B.first, A.second);
    pii res = cross<ll>(A-C1, B-C1) < 0 ? C1 : C2;
    return res;
}

std::pair<ld,ld> rectangle(int xmin, int ymin, int xmax, int ymax) {
    ll dx = xmax - xmin, dy = ymax - ymin;
    ld fi = (dx + 1) / 2 * dy;
    ld se = dx / 2 * dy;
    if (xmin % 2 != 0) std::swap(fi,se);
    return {fi, se};
}

ll sum(ll n) {
// n^2 - (n-1)^2 + (n-2)^2 - (n-3)^2 + (n-4)^2 + ...
    return n * (n+1) / 2;
}

std::pair<ld, ld> solveBaseCaseLD(ll x, ll y) {
// triangle
// *
// **
// ***
// ****
    ld c = y / (2.0L * x);
    std::pair<ld, ld> res{c * sum(x), c * sum(x-1)};
    return res;
}

std::pair<ld, ld> solveBaseCaseRU(ll x, ll y) {
// triangle
// ****
//  ***
//   **
//    *
    auto res = solveBaseCaseLD(x, y);
    if (x % 2 == 0)
        std::swap(res.first, res.second);
    return res;
}

std::pair<ld, ld> solveBaseCaseRU(ll xmin, ll ymin, ll xmax, ll ymax) {
// triangle
// ****
//  ***
//   **
//    *
    auto res = solveBaseCaseRU(xmax-xmin, ymax-ymin);
    if (xmin % 2 != 0) std::swap(res.first, res.second);
    return res;
}

std::pair<ld, ld> solveBaseCaseLD(ll xmin, ll ymin, ll xmax, ll ymax) {
// triangle
// *
// **
// ***
// ****
    auto res = solveBaseCaseLD(xmax-xmin, ymax-ymin);
    if (xmin % 2 != 0) std::swap(res.first, res.second);
    return res;
}

std::pair<ld, ld> solveBaseCaseRD(ll x, ll y) {
// triangle
//    *
//   **
//  ***
// ****
    auto res = solveBaseCaseLD(x, y);
    if (x % 2 == 0) std::swap(res.first, res.second);
    return res;
}

std::pair<ld, ld> solveBaseCaseLU(ll x, ll y) {
// triangle
// ****
// ***
// **
// *   
    auto res = solveBaseCaseLD(x, y);
    return res;
}

std::pair<ld, ld> solveBaseCaseLU(ll xmin, ll ymin, ll xmax, ll ymax) {
// triangle
// ****
// ***
// **
// *
    auto res = solveBaseCaseLU(xmax-xmin, ymax-ymin);
    if (xmin % 2 != 0) std::swap(res.first, res.second);
    return res;
}

std::pair<ld, ld> solveBaseCaseRD(ll xmin, ll ymin, ll xmax, ll ymax) {
// triangle
//    *
//   **
//  ***
// ****
    auto res = solveBaseCaseRD(xmax-xmin,ymax-ymin);
    if (xmin % 2 != 0)
        std::swap(res.first, res.second);
    return res;
}

std::pair<ld, ld> triangle(pii A, pii B, pii C) {
// B - corner
// AC - diagonal
    if (doubleSquare<ll>(A,B,C) == 0)
        return {0, 0};
    if (A.first > C.first)
        std::swap(A, C);
    ll xmin = std::min({A.first, B.first, C.first});
    ll xmax = std::max({A.first, B.first, C.first});
    ll ymin = std::min({A.second, B.second, C.second});
    ll ymax = std::max({A.second, B.second, C.second});
    pii LD(xmin,ymin), LU(xmin,ymax), RD(xmax,ymin), RU(xmax,ymax);
    std::pair<ld,ld> res;
    if (A.second > C.second) {
        if (B == LD) res = solveBaseCaseLD(xmin,ymin,xmax,ymax);
        else res = solveBaseCaseRU(xmin,ymin,xmax,ymax);
    } else {
        if (B == RD) res = solveBaseCaseRD(xmin,ymin,xmax,ymax);
        else res = solveBaseCaseLU(xmin,ymin,xmax,ymax);
    }
    return res;
}

std::pair<ld,ld> twoRectangles(pii A, pii B, pii C) {
    if (A.first > B.first) std::swap(A, B);
    if (A.first > C.first) std::swap(A, C);
    if (B.first > C.first) std::swap(B, C);
    assert(A.first <= B.first && B.first <= C.first);
    auto [ymin, ymax] = std::minmax({A.second,C.second});
    if (B.second >= ymax || B.second <= ymin || B.first == A.first || B.first == C.first) {
        remin(ymin, B.second);
        remax(ymax, B.second);
        return rectangle(A.first, ymin, C.first, ymax);
    }
    std::pair<ld,ld> rect = rectangle(A.first, ymin, C.first, ymax);
    // above or below than diagonal?
    if (rotation(A,C,B) <= 0) { // above
        // is A below than C?
        if (A.second <= C.second)
            rect = rect - rectangle(A.first, B.second, B.first, ymax);
        else
            rect = rect - rectangle(B.first, B.second, C.first, ymax);
    } else { // below
        // is A below than C?
        if (A.second <= C.second)
            rect = rect - rectangle(B.first, ymin, C.first, B.second);
        else
            rect = rect - rectangle(A.first, ymin, B.first, B.second);
    }
    return rect;
}

std::pair<ld,ld> calcTriangle(pii A, pii B, pii C) {
    if (cross<ll>(A-B,C-B) > 0)
        std::swap(A, C);
    auto temp = twoRectangles(A,B,C);
    auto P1 = pickPointOutside(A,B);
    auto P2 = pickPointOutside(B,C);
    auto P3 = pickPointOutside(C,A);
    if (!(A.first == B.first || A.second == B.second))
        temp = temp - triangle(A,P1,B);
    if (!(B.first == C.first || B.second == C.second))
        temp = temp - triangle(B,P2,C);
    if (!(C.first == A.first || C.second == A.second))
        temp = temp - triangle(C,P3,A);
    return temp;
}

ld solveFast(vpii points) {
    moveToPositive(points);
    transpose(points);
    makeCounterClockwise(points);
    ld answ = 0;
    pii A(0,0);
    for (int i = 0; i < isz(points); i++) {
        pii B = points[i], C = points[(i+1)%isz(points)];
        ld curr = calcTriangle(A, B, C).first;
        if (rotation(A,B,C) == LEFT) answ += curr;
        else answ -= curr;
    }
    return answ;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout << std::fixed << std::setprecision(12);
    auto points = readPolygon();
    std::cout << solveFast(points) << std::endl;
}
