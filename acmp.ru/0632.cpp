#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cassert>
#include <functional>

struct Segment {
    int x1, y1, x2, y2;
    
    static Segment read() {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        if (x2 < x1 || (x2 == x1 && y2 < y1)) {
            std::swap(x1, x2);
            std::swap(y1, y2);
        }
        return Segment{x1, y1, x2, y2};
    }
};

int main() {
    int W, H, nSeg;
    scanf("%d %d %d", &W, &H, &nSeg);
    std::vector<int> x{0, W}, y{0, H}; // вектора сжатых x и y координат
    std::vector<Segment> segments{
        Segment{0, 0, 0, H},
        Segment{W, 0, W, H},
        Segment{0, 0, W, 0},
        Segment{0, H, W, H}
    };
    for (int i = 0; i < nSeg; ++i) { // чтение отрезков
        auto s = Segment::read();
        if (s.x1 >= W || s.x2 <= 0 || s.y1 >= H || s.y2 <= 0) {
            continue;
        }
        s.x2 = std::min(W, s.x2);
        s.x1 = std::max(0, s.x1);
        s.y2 = std::min(H, s.y2);
        s.y1 = std::max(0, s.y1);
        x.push_back(s.x1);
        x.push_back(s.x2);
        y.push_back(s.y1);
        y.push_back(s.y2);
        segments.push_back(s);
    }
    
    std::sort(x.begin(), x.end()); // сжатие координат x
    x.erase(std::unique(x.begin(), x.end()), x.end());
    
    std::sort(y.begin(), y.end()); // сжатие координаты y
    y.erase(std::unique(y.begin(), y.end()), y.end());
    
    // Отмечаем сегменты как стенки на двумерном поле:
    const int WALL = -2, NOT_VISITED = -1;
    const int nRows = (int)y.size()*2-1, nCols = (int)x.size()*2-1;
    std::vector<std::vector<int>> part(nRows, std::vector<int>(nCols, NOT_VISITED));
    std::vector<std::vector<int>> square(nRows, std::vector<int>(nCols, -1));
    for (auto& s : segments) {
        s.x1 = int(std::lower_bound(x.begin(), x.end(), s.x1) - x.begin()) * 2;
        s.x2 = int(std::lower_bound(x.begin(), x.end(), s.x2) - x.begin()) * 2;
        s.y1 = int(std::lower_bound(y.begin(), y.end(), s.y1) - y.begin()) * 2;
        s.y2 = int(std::lower_bound(y.begin(), y.end(), s.y2) - y.begin()) * 2;
        assert(s.x1 == s.x2 || s.y1 == s.y2);
        if (s.y1 == s.y2) {
            for (int i = s.x1; i <= s.x2; ++i) {
                part[s.y1][i] = WALL;
                square[s.y1][i] = 0;
            }
        } else if (s.x1 == s.x2) {
            for (int i = s.y1; i <= s.y2; ++i) {
                part[i][s.x1] = WALL;
                square[i][s.x1] = 0;
            }
        } else {
            assert(false);
        }
    }
    // Вычисляем площадь каждого сжатого сегмента:
    for (int r = 0; r < nRows; ++r) {
        for (int c = 0; c < nCols; ++c) {
            if (r % 2 == 0 || c % 2 == 0) {
                square[r][c] = 0;
            } else {
                assert(r % 2 == 1 && c % 2 == 1);
                square[r][c] = (y[r/2+1]-y[r/2])*(x[c/2+1]-x[c/2]);
            }
        }
    }
    // Заливка - выделяем компоненты связности:
    int nParts = 0;
    for (int r = 0; r < nRows; ++r) {
        for (int c = 0; c < nCols; ++c) {
            if (part[r][c] == NOT_VISITED) {
                std::function<void(int, int)> visit = [&](const int row, const int col) {
                    part[row][col] = nParts;
                    for (int dr = -1; dr <= 1; ++dr) {
                        for (int dc = -1; dc <= 1; ++dc) {
                            if (dr * dr + dc * dc == 1 && part[row+dr][col+dc] == NOT_VISITED) {                                
                                part[row+dr][col+dc] = nParts;
                                visit(row+dr, col+dc);
                            }
                        }
                    }
                };
                visit(r, c); 
                ++nParts;
            }
        }
    }
    // Считаем площадь каждой компоненты связности:
    std::vector<int> s(nParts);
    for (int r = 0; r < nRows; ++r) {
        for (int c = 0; c < nCols; ++c) {
            if (part[r][c] != WALL) {
                assert(part[r][c] >= 0);
                s[part[r][c]] += square[r][c];
            }
        }
    }
    std::sort(s.begin(), s.end(), std::greater<int>());
    for (auto& it : s) {
        printf("%d\n", it);
    }
    return 0;
}