#include <iostream>

bool solve(int x1, int y1, int r1, int x2, int y2, int r2) {
    int dist2 = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
    if (dist2 > (r1+r2)*(r1+r2)) {
        return false;
    }
    if (dist2 < (r1-r2)*(r1-r2)) {
        return false;
    }
    return true;
}

int main() {
  	int x1, y1, r1, x2, y2, r2;
  	std::cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
  	if (r1 < r2) {
        std::swap(r1, r2);
        std::swap(x1, x2);
        std::swap(y1, y2);
    }
  	std::cout << (solve(x1, y1, r1, x2, y2, r2) ? "YES" : "NO") << std::endl;
	return 0;
}