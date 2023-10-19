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

using Triangle = std::tuple<pii,pii,pii>;

inline bool isPointInsideTriangle(Triangle tr, pii p) {
    auto [A, B, C] = tr;
    auto S = doubleSquare<ll>(A,B,C);
    auto S1 = doubleSquare<ll>(p,B,C);
    auto S2 = doubleSquare<ll>(A,p,C);
    auto S3 = doubleSquare<ll>(A,B,p);
    return S == S1 + S2 + S3;
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

inline bool isPointOnSegment(pii P, pii A, pii B) {
    auto [x, y] = P;
    auto [xmin,xmax] = std::minmax({A.first, B.first});
    auto [ymin,ymax] = std::minmax({A.second, B.second});
    if (x < xmin || x > xmax || y < ymin || y > ymax)
        return false;
    return cross<ll>(A-P,B-P) == 0;
}

const int NONE = 0, POINT = 1, INSIDE = 2;
inline int intersects(pii A, pii B, pii C, pii D) {
    if (A == C || A == D || B == C || B == D)
        return POINT;
    if (isPointOnSegment(A,C,D) || isPointOnSegment(B,C,D) ||
        isPointOnSegment(C,A,B) || isPointOnSegment(D,A,B))
        return POINT;
    auto [xmin1,xmax1] = std::minmax({A.first, B.first});
    auto [ymin1,ymax1] = std::minmax({A.second, B.second});
    auto [xmin2,xmax2] = std::minmax({C.first, D.first});
    auto [ymin2,ymax2] = std::minmax({C.second, D.second});
    if (xmax1 < xmin2 || xmin1 > xmax2)
        return NONE;
    if (ymax1 < ymin2 || ymin1 > ymax2)
        return NONE;
    auto rot1 = rotation(A,B,C);
    auto rot2 = rotation(A,B,D);
    if (sign(rot1) * sign(rot2) < 0)
        return INSIDE;
    return NONE;
}

inline bool isAlmostEqual(ld x, ld y) {
    const ld EPS = 1e-10;
    return std::abs(x-y) / (1 + std::abs(x)) < EPS;
}

inline bool angleLessThanPi(pii L, pii M, pii R) {
    return rotation(L,M,R) == LEFT;
}

inline bool angleGreaterThanPi(pii L, pii M, pii R) {
    return rotation(L,M,R) == RIGHT;
}

inline auto getPrev(const auto &vec, int i) {
    i--;
    if (i < 0) i = isz(vec)-1;
    return vec[i];
}

inline auto getNext(const auto &vec, int i) {
    i++;
    if (i == isz(vec))
        i = 0;
    return vec[i];
}

inline bool isConvex(const vpii &P) {
    for (int i = 0; i < isz(P); i++)
        if (rotation(getPrev(P, i), P[i], getNext(P, i)) == RIGHT)
            return false;
    return true;
}

inline void removeSameLine(vpii &P) {
    static std::vector<bool> keep;
    keep.assign(isz(P), false);
    for (int i = 0; i < isz(P); i++)
        keep[i] = (rotation(getPrev(P,i), P[i], getNext(P,i)) != 0);
    int p = 0;
    for (int i = 0; i < isz(P); i++)
        if (keep[i]) P[p++] = P[i];
    P.resize(p);
}

} // namespace geoma
} // namespace algos
#endif // __GEOMA_HPP__