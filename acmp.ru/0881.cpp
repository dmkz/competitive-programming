#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <cassert>
#include <iostream>
#include <string>

const int L = 0, R = 1, U = 2, D = 3;
const int drow[] = {  0,  0, -1,  1};
const int dcol[] = { -1,  1,  0,  0};

const int WALL  = 1;
const int EMPTY = 0;

struct Robot {
    int row, col, dir, wall_row, wall_col;
    
    void step() {
        row += drow[dir];
        col += dcol[dir];
    }
    
    void crush() {
        row = wall_row;
        col = wall_col;
    }
    
    inline bool alive() const {
        return !(row == wall_row && col == wall_col);
    }
    
    inline bool equal(const Robot& r) {
        return row == r.row && col == r.col;
    }
    
    inline bool include(const Robot& r) {
        int rmin = std::min(row, wall_row);
        int cmin = std::min(col, wall_col);
        int rmax = std::max(row, wall_row);
        int cmax = std::max(col, wall_col);
        return rmin <= r.row && r.row <= rmax && cmin <= r.col && r.col <= cmax;
    }
};

int main() {
    int nCols, nRows, nRobots;
    scanf("%d %d %d", &nCols, &nRows, &nRobots);
    
    std::vector<std::vector<int>> field(1+nRows+1, std::vector<int>(1+nCols+1, WALL));
    
    for (int row = 1; row <= nRows; ++row) {
        for (int col = 1; col <= nCols; ++col) {
            char c; scanf(" %c", &c);
            field[row][col] = (c == 'X' ? WALL : EMPTY);
        }
    }
    
    std::vector<Robot> robots;
    
    for (int i = 0; i < nRobots; ++i) {
        int c, r; char dir;
        scanf("%d %d %c", &c, &r, &dir);
        int side = -1;
        switch (dir) {
            case 'L': side = L; break;
            case 'R': side = R; break;
            case 'U': side = U; break;
            case 'D': side = D; break;
        }
        assert(side >= 0);
        int nr = r, nc = c;
        while (field[nr][nc] == EMPTY) {
            nr += drow[side];
            nc += dcol[side];
        }
        robots.push_back(Robot{r,c,side,nr,nc});
    }
    
    int t = 0;
    while (true) {
        if (debug) printf("t = %d, nRobots = %d\n", t, nRobots);
        // 1. Если робот оказался за пределами лабиринта или в клетке, которая заполнена стеной, то он взрывается
        // Обрабатывается автоматически
        std::queue<int> queue;
        // 2. Если в какой-то клетке оказалось два или более робота, то все они взрываются;
        for (int i = 0; i < (int)robots.size(); ++i) {
            if (!robots[i].alive()) continue;
            for (int j = 0; j < (int)robots.size(); ++j) {
                if (i == j || !robots[j].alive()) continue;
                if (robots[i].equal(robots[j])) {
                    queue.push(i);
                }
            }
        }
        while (!queue.empty()) {
            auto id = queue.front(); queue.pop();
            if (robots[id].alive()) {
                robots[id].crush();
            }
        }
        // 3. Остальное
        for (int i = 0; i < (int)robots.size(); ++i) {
            if (!robots[i].alive()) continue;
            for (int j = 0; j < (int)robots.size(); ++j) {
                if (i == j || !robots[j].alive()) continue;
                if (robots[j].include(robots[i])) {
                    queue.push(i);
                }
            }
        }
        while (!queue.empty()) {
            auto id = queue.front(); queue.pop();
            if (robots[id].alive()) {
                robots[id].crush();
            }
        }
        // Шаг для всех роботов
        bool flag = false;
        for (auto& r : robots) {
            if (r.alive()) {
                flag = true;
                r.step();
            }
        }
        if (flag) {
            ++t;
        } else {
            break;
        }
    }
    printf("%d", t);
    return 0;
}