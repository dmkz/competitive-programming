#ifndef __CONVEXHULLTRICK_HPP__
#define __CONVEXHULLTRICK_HPP__

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
#endif // __CONVEXHULLTRICK_HPP__