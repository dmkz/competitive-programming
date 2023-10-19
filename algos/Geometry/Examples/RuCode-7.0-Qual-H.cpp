#pragma GCC optimize("Ofast")
#include "template.hpp"
#include "debug.hpp"
#include "geoma.hpp"
#include "triangulate.hpp"
using namespace algos::triangulate;
using namespace algos::geoma;

pii pickPointOutside(pii A, pii B) {
    pii C1(A.first, B.second);
    pii C2(B.first, A.second);
    pii res = cross<ll>(A-C1, B-C1) < 0 ? C1 : C2;
    watch("pickPointOutside", A, B, res);
    return res;
}

std::pair<ld,ld> rectangle(int xmin, int ymin, int xmax, int ymax) {
    ll dx = xmax - xmin, dy = ymax - ymin;
    ld fi = (dx + 1) / 2 * dy;
    ld se = dx / 2 * dy;
    if (xmin % 2 != 0) std::swap(fi,se);
    watch("rectangle", xmin, ymin, xmax, ymax, fi, se);
    return {fi, se};
}

ll sum(ll n) {
// n^2 - (n-1)^2 + (n-2)^2 - (n-3)^2 + (n-4)^2 + ...
// wolfram: n*(n+1)/2
// check: 4^2-3^2+2^1-1=16-9+4-1=10
// check: 4 * 5 / 2 = 10
    return n * (n+1) / 2;
}

std::pair<ld, ld> solveBaseCaseLD(ll x, ll y) {
// triangle
// *
// **
// ***
// ****
    watch("solveBaseCaseLD",x,y);
    ld c = y / (2.0L * x);
    std::pair<ld, ld> res{c * sum(x), c * sum(x-1)};
    watch(res);
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
        std::swap(res.first, res.second); // проверено
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
    if (x % 2 == 0) // проверено
        std::swap(res.first, res.second);
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

bool inter(pii A, pii B, int x, ld &y) {
    if (A.first > B.first) std::swap(A, B);
    if (x < A.first || x > B.first)
        return false;
    if (x == A.first) {
        y = A.second;
        return true;
    }
    if (x == B.first) {
        y = B.second;
        return true;
    }
    pii v = B - A;
    // A + t * (B - A) == {x, y}
    // A.first + t * v.first == x
    ld t = (x - A.first) / ld(v.first);
    y = A.second + t * v.second;
    return true;
}

ld solveVerticalCase(pii A, pii B, pii C, int x) {
    std::vector<ld> y1, y2;
    ld y;
    if (inter(A,B,x,y)) y1 << y;
    if (inter(B,C,x,y)) y1 << y;
    if (inter(A,C,x,y)) y1 << y;
    if (inter(A,B,x+1,y)) y2 << y;
    if (inter(B,C,x+1,y)) y2 << y;
    if (inter(A,C,x+1,y)) y2 << y;
    std::sort(all(y1));
    std::sort(all(y2));
    ld res = (y1.back() - y1.front() + y2.back() - y2.front()) / 2;
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
    // выше или ниже диагонали?
    if (rotation(A,C,B) <= 0) { // выше
        // A ниже чем C?
        if (A.second <= C.second)
            rect = rect - rectangle(A.first, B.second, B.first, ymax);
        else
            rect = rect - rectangle(B.first, B.second, C.first, ymax);
    } else { // ниже
        // A ниже чем C?
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

ld calcTriangleSlow(pii A, pii B, pii C) {
    auto [xMin, xMax] = std::minmax({A.first, B.first, C.first});
    ld ans{};
    int x = xMin;
    if (x % 2 != 0)
        x++;
    while (x+1 <= xMax) {
        assert(x % 2 == 0);
        ans += solveVerticalCase(A,B,C,x);
        x += 2;
    }
    return ans;
}

void stress(int xs, int xf) {
    //const int X = 10;
    for (int x1 = xs; x1 <= xf; x1++)
        for (int y1 = xs; y1 <= xf; y1++)
            for (int x2 = xs; x2 <= xf; x2++)
                for (int y2 = xs; y2 <= xf; y2++)
                    for (int x3 = xs; x3 <= xf; x3++)
                        for (int y3 = xs; y3 <= xf; y3++) {
                            pii A(x1,y1), B(x2,y2), C(x3,y3);
                            ll s = doubleSquare<ll>(A,B,C);
                            if (s == 0) continue;
                            ld fast = calcTriangle(A,B,C).first;
                            ld slow = calcTriangleSlow(A,B,C);
                            if (!isAlmostEqual(fast,slow)) {
                                debug = 1;
                                fast = calcTriangle(A,B,C).first;
                                watch(A,B,C);
                                watch(fast);
                                watch(slow);
                                std::exit(0);
                            }
                        }
}

std::mt19937 gen;

int randInt(int a, int b) {
    assert(a <= b);
    return std::uniform_int_distribution<int>(a,b)(gen);
}

vpii generatePoly(int xmin, int xmax, int ymin, int ymax, int n, int limit = 1e6) {
    //bool debug = 1;
    std::set<pii> used;
    auto randPoint = [&](){
        while (true) {
            int x = randInt(xmin, xmax);
            int y = randInt(ymin, ymax);
            if (!used.count(pii(x,y)))
                return pii(x, y);
        }
    };
    vpii kek;
    auto pushPoint = [&](pii p) {
        kek << p;
        used << p;
    };
    pushPoint(randPoint());
    pushPoint(randPoint());
    pushPoint(randPoint());
    while (isz(kek) < n) {
        int attempts = 0;
        while (attempts < limit) {
            attempts++;
            auto p = randPoint();
            int nP{}, nI{};
            for (int i = 0; i + 1 < isz(kek); i++) {
                int t = intersects(kek.back(), p, kek[i], kek[i+1]);
                nP += (t == POINT);
                nI += (t == INSIDE);
            }
            if (!(nI == 0 && nP == 1))
                continue;
            nP = nI = 0;
            for (int i = 0; i + 1 < isz(kek); i++) {
                int t = intersects(kek.front(), p, kek[i], kek[i+1]);
                nP += (t == POINT);
                nI += (t == INSIDE);
            }
            if (nI == 0 && nP == 1) {
                pushPoint(p);
                break;
            }
        }
        if (attempts >= 1000)
            break;
    }
    if (orientedSquare(kek) < 0)
        std::reverse(all(kek));
    return kek;
}

void testMonotone() {
    //bool debug = 1;
    //vpii P{{14,5},{12,6},{11,11},{8,10},{7,11},{3,9},{6,8},{5,5},{2,7},{1,3},{4,1},{7,2},{10,1},{9,4},{13,3}};
    //vpii P{{-3, 5}, {-1, 5}, {4, 5}, {-4, 8}, {-7, 9}, {-10, 5}, {6, -3}, {5, -2}, {-4, 4
//}, {9, 4}};
    //vpii P{{-7, 8}, {-4, 2}, {-9, -9}, {2, 9}, {1, 10}, {-1, 10}, {-5, 9}, {-4, 10}, {-6,
 //10}, {-9, 5}};
    //vpii P{{-10, 6}, {-9, 1}, {-6, -9}, {-6, -3}, {-4, -5}, {-3, -4}, {9, -3}, {-2, 4}, {
//-1, 0}, {-7, -1}};
    //vpii P{{7, -6}, {6, -6}, {6, -4}, {3, 9}, {4, -7}, {1, -10}, {8, -9}, {8, 0}, {7, -1}
//, {6, 7}};
    //vpii P{{3, 5}, {-2, 9}, {3, -5}, {3, -4}, {4, -7}, {9, -6}, {9, -5}, {8, -2}, {2, 7},
 //{7, -1}};
 vpii P{{9, 1}, {6, 1}, {10, 2}, {6, 2}, {10, 4}, {7, 5}, {5, 5}, {4, 10}, {-2, -1}, {
10, 1}};
    //vpii P{{5, -6}, {10, 9}, {7, 0}};
    std::cout << triangulateFast(P).size() << std::endl;
    
    for (int nTests = 0; nTests <= 10000; nTests++) {
        watch("start generate P");
        while (true) {
            //P = generatePoly(-10,10,-10,10,10);
            //P = generatePoly(-100,100,-100,100,100);
            P = generatePoly(-1e9,1e9,-1e9,1e9,2000);
            ll s = orientedSquare(P);
            if (s != 0)
                break;
        }
        watch("P: generated");
        //print("poly2.txt", {P},P,{});
        //watch(P);
        //break;
        std::cout << triangulateFast(P).size() << " ";
        //print("poly.txt", PP, P, D);
    }
    std::cout << "OK" << std::endl;
    std::exit(0);
}

vpii genWorst1() {
    const int XMIN = -(int)1e9;
    const int XMAX = +(int)1e9;
    const int YMAX = +(int)1e9;
    vpii left;
    for (int i = 0; i < 25000; i++) {
        left.emplace_back(XMIN, YMAX-2*i);
        left.emplace_back(XMAX-1, YMAX-(2*i+1));
    }
    vpii right = left;
    for (auto &[x,y] : right) x++;
    std::reverse(all(right));
    return left << right;
}

vpii genWorst2() {
    const int XMAX = +(int)1e9;
    const int YMIN = -(int)1e9;
    const int YMAX = +(int)1e9;
    vpii top;
    for (int i = 0; i < 25000; i++) {
        top.emplace_back(XMAX-2*i, YMIN);
        top.emplace_back(XMAX-(2*i+1), YMAX-1);
    }
    vpii bottom = top;
    for (auto &[x,y] : bottom) y++;
    std::reverse(all(bottom));
    return top << bottom;
}

ld accumulateTriangles(const std::vector<Triangle> &triangles) {
    ld ans{};
    for (auto &[A,B,C] : triangles)
        ans += calcTriangle(A,B,C).first;
    return ans;
}

ld solveAllSubtasks(vpii points) {
    moveToPositive(points);
    transpose(points);
    makeCounterClockwise(points);
    std::vector<Triangle> triangles = isz(points) <= 1000 ? triangulateSlow(points)
                                    : isConvex(points) ? triangulateConvex(points)
                                                       : triangulateFast(points);
    return accumulateTriangles(triangles);
}

ld solveFast(vpii points) {
    moveToPositive(points);
    transpose(points);
    makeCounterClockwise(points);
    ld answ = 0;
    triangulateFast(points, [&](const vpii &tr){
        assert(isz(tr) <= 3);
        if (isz(tr) == 3)
            answ += calcTriangle(tr[0],tr[1],tr[2]).first;
    });
    return answ;
}
#include "timer.hpp"
void testWorst1() {
    std::cout << __FUNCTION__ << ": ";
    Timer timer;
    timer.start();
    vpii P = genWorst1();
    ld answ = solveFast(P);
    timer.finish();
    std::cout << "answ = " << answ << ", runtime = " << timer() << " ms" << std::endl;
}

void testWorst2() {
    std::cout << __FUNCTION__ << ": ";
    Timer timer;
    timer.start();
    vpii P = genWorst2();
    ld answ = solveFast(P);
    timer.finish();
    std::cout << "answ = " << answ << ", runtime = " << timer() << " ms" << std::endl;
}

void testAll() {
    testWorst1();
    testWorst2();
    std::exit(0);
}

int main() {
    //testMonotone();
    //testAll();
    //testMonotone();
    auto points = readPolygon();
    std::cout << solveFast(points) << std::endl;
}
