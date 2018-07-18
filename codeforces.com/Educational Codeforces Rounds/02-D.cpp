/*
    Problem: 600D. Area of Two Circles' Intersection

    Solution: geometry, area of the circle segment, circles intersection, O(1)
*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <functional>
#include <cassert>
#include <cstdint>
#include <algorithm>

typedef long double Real;

const Real PI = std::acos(-1.0L);

Real solve(Real x1, Real y1, Real r1, Real x2, Real y2, Real r2) {
    assert(r1 >= r2);
    
    Real dist2 = (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
    
    if (dist2 >= (r1+r2)*(r1+r2)) { // if no intersect - answer is 0
        return 0;
    }
    
    // If the smaller circle lies inside the larger one: r1 >= dist + r2
    if ((r1-r2)*(r1-r2) >= dist2) {
        return PI * r2 * r2;
    }
    
    std::function<Real(Real, Real, Real)> angle = [](Real a, Real b, Real c) {
        // Compute the angle opposite by the cosine theorem
        // a^2 = b^2+c^2-2*b*c*cos(alpha)
        return std::acos((b*b+c*c-a*a) / b / c / 2);
    };
    
    std::function<Real(Real, Real)> S = [](Real r, Real angle) {
    	// Segment area
    	// r - circle radius, angle - angle between sides
    	return r * r * (angle / 2 - std::sin(angle) / 2);
    };
    
    Real  dist = std::sqrt(dist2);        // distance between circles centers
	Real alpha = 2 * angle(r2, r1, dist); // angle in larger circle
    Real  beta = 2 * angle(r1, r2, dist); // angle in smaller circle
    return S(r1, alpha) + S(r2, beta);
}

int main() {    

    Real x1, y1, r1, x2, y2, r2; 
    std::cin >> x1 >> y1 >> r1;
    std::cin >> x2 >> y2 >> r2;
    
    if (r1 < r2) {
        std::swap(x1, x2);
        std::swap(y1, y2);
        std::swap(r1, r2);
    }
    
    std::cout << std::fixed << std::setprecision(6) << solve(x1, y1, r1, x2, y2, r2) << std::endl;
    
    return 0;
}