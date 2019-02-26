// Given set of lines and set of points, need to calculate for each point maximal value of a * x + b among set of lines
// Link: https://codeforces.com/gym/101341/problem/L

#include <bits/stdc++.h>

namespace ConvexHullTrick {
    
    template<typename TPoint, typename TLine>
    struct LowerEnvelope {
        // Contains lower envelope of set of lines k * x + b
        // lines should be added in order of decreasing k
        std::vector<TLine> ln;
        
        void push(const TLine& L) {
            for (int n = (int)ln.size(); n > 1; ) {
                TPoint A = intersect(ln[n-1], ln[n-2]);
                TPoint B = intersect(ln[n-1], L);
                if (A.x < B.x) { break; }
                else { ln.pop_back(); n--; }
            }
            ln.push_back(L);
        }
        
        const TLine& getMin(TPoint p) {
            if (ln.size() == 1u) { return ln[0]; }
            int low = -1, high = (int)ln.size()-1;
            // Invariant: p <= intersect(ln[high], ln[high+1])
            while (high - low > 1) {
                int mid = (low + high) / 2;
                TPoint P = intersect(ln[mid], ln[mid+1]);
                if (p.x <= P.x) { high = mid; }
                else { low = mid; }
            }
            return ln[high];
        }
    };

    typedef long double Real;
    
    struct Point {
        Real x, y;
        Point(Real x_ = Real(0), Real y_ = Real(0)) 
            : x(x_), y(y_) { }
    };

    struct Line {
        // y = a * x + b;
        Real a, b; int id;
        Line(Real a_ = Real(0), Real b_ = Real(0), int id_ = 0) 
            : a(a_), b(b_), id(id_) { }
    };

    Point intersect(const Line& lhs, const Line& rhs) {
        // lhs.a * x + lhs.b == rhs.a * x + rhs.b
        // (lhs.a - rhs.a) * x == (rhs.b - lhs.b);
        Real x = (rhs.b - lhs.b) / (lhs.a - rhs.a);
        return Point(x, lhs.a * x + lhs.b);
    }
}

#define all(x) (x).begin(), (x).end()

struct Pair { int x, id; };

bool operator<(const Pair& lhs, const Pair& rhs) {
    return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.id < rhs.id); 
}

struct Triple { int min, max, id; };

bool operator<(const Triple& lhs, const Triple& rhs) {
    return lhs.max > rhs.max || (lhs.max == rhs.max && (lhs.min > rhs.min || (lhs.min == rhs.min && lhs.id < rhs.id)));
}

int main() {
    using namespace ConvexHullTrick;
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int nT, nP;
    // Input triples:
    std::cin >> nT;
    std::set<Triple> tr;
    for (int i = 1, a, b; i <= nT; ++i) {
        std::cin >> a >> b; 
        tr.insert(Triple{a,b,i});
    }
    // Input pairs:
    std::cin >> nP;
    std::set<Pair> pr;
    for (int i = 1, x; i <= nP; ++i) {
        std::cin >> x;
        pr.insert(Pair{x, i});
    }
    // Resolve problem where Triple.min == Triple.max:
    std::vector<int> answ(1+nP);
    for (auto it = tr.begin(); it != tr.end(); ) {
        auto next = std::next(it);
        while (!pr.empty() && pr.begin()->x <= it->min) {
            answ[pr.begin()->id] = it->id;
            pr.erase(pr.begin());
        }
        if (it->min == it->max) { tr.erase(it); }
        it = next;
    }
    // Erase not interesting triples:
    int max = INT_MIN;
    for (auto it = tr.begin(); it != tr.end(); ) {
        auto next = std::next(it);
        if (it->min <= max) { tr.erase(it); }
        else { max = it->min; }
        it = next;
    }
    // Prepare Lower Envelope for sets of given lines:
    LowerEnvelope<Point,Line> lower;
    for (auto it = tr.rbegin(); it != tr.rend(); it++) {
        lower.push(Line(1 / Real(it->max - it->min), - it->max / Real(it->max - it->min), it->id));
    }
    // If all triples were already removed, answer to other queries with default value:
    if (tr.empty()) {
        for (auto it = pr.begin(); it != pr.end(); ) {
            auto next = std::next(it);
            if (!answ[it->id]) { answ[it->id] = 1; }
            it = next;
        }
    }
    // Answer to queries:
    for (auto it = pr.begin(); it != pr.end(); ) {
        auto next = std::next(it);
        if (!answ[it->id]) { answ[it->id] = lower.getMin(it->x).id; }
        it = next;
    }
    // Output answers:
    for (int i = 1; i <= nP; ++i) {
        std::cout << std::max(1, answ[i]) << ' ';
    }
    std::cout << std::endl;
    return 0;
}