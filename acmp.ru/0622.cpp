/*
    Сведем задачу к задаче на графы: 
    - Читаем все прямоугольники, сохраняя куда-нибудь их координаты x и y
    - Сортируем координаты, удаляем повторы
    - Каждой координате сопоставляем ее удвоенный индекс в полученном массиве
    - Таким образом, мы свели задачу к задаче на прямоугольном поле со стенками и комнатами
    - Считаем количество областей смежности
    
    Пример для первого теста:
    3
    10 20 50 30
    40 10 50 25
    40 25 80 30
    
    Полученное после всех преобразований поле:
    ###########
    #000000000#
    #000###000#
    #000#1#000#
    #0#####000#
    #0#2#3#000#
    #0#2#####0#
    #0#2#4#5#0#
    #0#######0#
    #000000000#
    ###########
    Ответ: 6
*/


#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <cassert>
#include <functional>

struct Rect {
    int x_min, y_min, x_max, y_max;
    
    Rect(int x1, int y1, int x2, int y2) 
        : x_min(std::min(x1, x2))
        , y_min(std::min(y1, y2))
        , x_max(std::max(x1, x2))
        , y_max(std::max(y1, y2))
    { }
    
    static Rect read() {
        int x1, y1, x2, y2; 
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        return Rect(x1, y1, x2, y2);
    }
};

struct Point {
    int row, col;
};

int main() {
    int nRect; 
    scanf("%d", &nRect);
    
    std::vector<Rect> rects;
    for (int i = 0; i < nRect; ++i) {
        rects.push_back(Rect::read());
    }
    
    std::vector<int> x{-100001, 100001}, y{-100001, 100001};
    for (auto r : rects) {
        x.push_back(r.x_min);
        x.push_back(r.x_max);
        y.push_back(r.y_min);
        y.push_back(r.y_max);
    }
    
    std::sort(x.begin(), x.end());
    x.erase(std::unique(x.begin(), x.end()), x.end());
    
    std::sort(y.begin(), y.end());
    y.erase(std::unique(y.begin(), y.end()), y.end());
    
    const int WALL  = -2;
    const int EMPTY = -1;
    
    std::vector<std::vector<int>> map(2*y.size()-1, std::vector<int>(2*x.size()-1, EMPTY));
    
    for (int i = 0; i < (int)map.size(); ++i) {
        map[i].back() = map[i].front() = WALL;
    }
    
    for (int j = 0; j < (int)map[0].size(); ++j) {
        map.front()[j] = map.back()[j] = WALL;
    }
    
    for (const auto& it : rects) {
        int l = 2 * int(std::lower_bound(x.begin(), x.end(), it.x_min) - x.begin());
        int r = 2 * int(std::lower_bound(x.begin(), x.end(), it.x_max) - x.begin());
        int u = 2 * int(std::lower_bound(y.begin(), y.end(), it.y_min) - y.begin());
        int d = 2 * int(std::lower_bound(y.begin(), y.end(), it.y_max) - y.begin());
        for (int row = u; row <= d; ++row) {
            map[row][l] = map[row][r] = WALL;
        }
        for (int col = l; col <= r; ++col) {
            map[d][col] = map[u][col] = WALL;
        }
    }
    
    int count = 0;
    for (int row = 0; row < (int)map.size(); ++row) {
        for (int col = 0; col < (int)map[0].size(); ++col) {
            if (map[row][col] == EMPTY) {
                std::function<void(int, int, int)> bfs = [&map](int row, int col, int color) {
                    std::queue<Point> queue;
                    map[row][col] = color;
                    queue.push(Point{row, col});
                    while (!queue.empty()) {
                        auto curr = queue.front(); queue.pop();
                        for (int dr = -1; dr <= 1; ++dr)
                            for (int dc = -1; dc <= 1; ++dc) {
                                if (dr * dr + dc * dc == 1) {
                                    int nr = curr.row + dr;
                                    int nc = curr.col + dc;
                                    if (map[nr][nc] == EMPTY) {
                                        map[nr][nc] = color;
                                        queue.push(Point{nr, nc});
                                    }
                                }
                            }
                    }
                };
                bfs(row, col, count++);
            }
        }
    }    
    printf("%d\n", count);
    
    return 0;
}