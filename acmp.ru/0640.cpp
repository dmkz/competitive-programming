/*
    "Test-The-Best": геометрия, преобразования фигур, O(n^2*log(n))
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>

typedef std::vector<char> Vector;
typedef std::vector<Vector> Matrix;

Matrix input() {
    int nRows, nCols;
    scanf("%d %d", &nRows, &nCols);
    
    Matrix temp(nRows, Vector(nCols));
    int minr = nRows, minc = nCols, maxr = -1, maxc = -1;
    for (int r = 0; r < nRows; ++r) {
        for (int c = 0; c < nCols; ++c) {
            char v; scanf(" %c", &v);
            temp[r][c] = (v == '#');
            if (temp[r][c]) {
                minr = std::min(minr, r);
                minc = std::min(minc, c);
                maxr = std::max(maxr, r);
                maxc = std::max(maxc, c);
            }
        }
    }
    if (maxr == -1) {
        return Matrix();
    }
    Matrix answ(maxr-minr+1, Vector(maxc-minc+1));
    for (int i = 0; i < (int)answ.size(); ++i) {
        for (int j = 0; j < (int)answ[0].size(); ++j) {
            answ[i][j] = temp[minr+i][minc+j];
        }
    }
    return answ;
}

Matrix rot(const Matrix& a) {
    const int nRows = a.size(), nCols = a[0].size();
    Matrix b(nCols, Vector(nRows));
    for (int r = 0; r < nRows; ++r) {
        for (int c = 0; c < nCols; ++c) {
            b[c][nRows-r-1] = a[r][c];
        }
    }
    return b;
}

Matrix sym(Matrix a) {
    for (auto& row : a) {
        std::reverse(row.begin(), row.end());
    }
    return a;
}

int main() {
    auto a = input(), b = input();
    std::set<Matrix> set;
    std::queue<Matrix> queue;
    queue.push(a);
    while (!queue.empty()) {
        Matrix next;
        next = rot(queue.front());
        if (set.find(next) == set.end()) {
            set.insert(next);
            queue.push(next);
        }
        next = sym(queue.front());
        if (set.find(next) == set.end()) {
            set.insert(next);
            queue.push(next);
        }
        queue.pop();
    }
    for (auto& a : set) {
        if (a == b) {
            printf("Yes");
            return 0;
        }
    }
    printf("No");
    return 0;
}