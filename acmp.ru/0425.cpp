#pragma GCC diagnostic ignored "-Wunused-result"

#include <bits/stdc++.h>

struct Segment {
    int x1, y1, x2, y2;
    
    Segment(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0) 
        : x1(x1), y1(y1), x2(x2), y2(y2) { }
    
    int x_min() const { return std::min(x1, x2); }
    int y_min() const { return std::min(y1, y2); }
    int x_max() const { return std::max(x1, x2); }
    int y_max() const { return std::max(y1, y2); }
    
    bool intersect(const Segment& other) const {
        if (x_max() < other.x_min() || x_min() > other.x_max() || y_max() < other.y_min() || y_min() > other.y_max()) return false;
        auto v1 = 1LL * (other.x1 - x1) * (y2 - y1) - 1LL * (other.y1 - y1) * (x2 - x1);
        auto v2 = 1LL * (other.x2 - x1) * (y2 - y1) - 1LL * (other.y2 - y1) * (x2 - x1);
        return v1 == 0 || v2 == 0 || (v1 < 0 && v2 > 0) || (v1 > 0 && v2 < 0);
    }
};

struct Point { 
    int row, col; 
};

bool square_intersect(int row, int col, const Segment& line) {
    Segment diag1(100 * row, 100 * col, 100 * (row+1), 100 * (col+1));
    Segment diag2(100 * (row+1), 100 * col, 100 * row, 100 * (col+1));
    return line.intersect(diag1) || line.intersect(diag2);
}

int solveSlow(int n, const Segment& line) {
    int answ = 0;
    for (int row = 0; row < n; ++row)
        for (int col = 0; col < n; ++col)
            answ += square_intersect(row, col, line);
    return answ;
}

int solveFast(int n, const Segment& line) {
    std::vector<std::vector<bool>> visited(n, std::vector<bool>(n, false));
    Point p1{0, std::min(n-1, line.y1 / 100)};
    assert(square_intersect(p1.row, p1.col, line));
    int answ = 0;
    std::queue<Point> queue;
    queue.push(p1);
    while (!queue.empty()) {
        auto curr = queue.front(); queue.pop();
        if (!visited[curr.row][curr.col]) {
            visited[curr.row][curr.col] = true;
            answ++;
        }
        for (int dr = -1; dr <= 1; ++dr) {
            for (int dc = -1; dc <= 1; ++dc) {
                if (dr * dr + dc * dc == 1) {
                    int nr = curr.row + dr, nc = curr.col + dc;
                    if (nr < 0 || nr >= n || nc < 0 || nc >= n || visited[nr][nc]) continue;
                    if (square_intersect(nr, nc, line)) {
                        visited[nr][nc] = true;
                        ++answ;
                        queue.push({nr, nc});
                    }
                }
            }
        }
    }
    return answ;
}

int main() {
    int n, y1, y2; 
    scanf("%d %d %d", &n, &y1, &y2); 
    Segment line(0, y1, n*100, y2);
    printf("%d\n", solveFast(n, line));
    return 0;
}