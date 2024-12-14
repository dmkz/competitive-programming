#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using namespace std;
void part1() {
    // чтение
    //p=0,4 v=3,-3
    string s;
    const int t = 100;
    const int width = 101;
    const int height = 103;
    int64_t count00{}, count01{}, count10{}, count11{};
    while (getline(cin, s)) {
        int x, y, vx, vy;
        int code = sscanf(s.c_str(), "p=%d,%d v=%d,%d", &x, &y, &vx, &vy);
        assert(code == 4);
        // x + t * vx
        // y + t * vy
        // осуществляем смещение:
        x += t * vx;
        y += t * vy;
        // определяем, в какой клетке поля мы находимся после смещения:
        x %= width;
        if (x < 0) x += width;
        y %= height;
        if (y < 0) y += height;
        // увеличиваем ответ
        if (x < width / 2) {
            if (y < height / 2) {
                count00++;
            } else if (y > height / 2) {
                count01++;
            }
        } else if (x > width / 2) {
            if (y < height / 2) {
                count10++;
            } else if (y > height / 2) {
                count11++;
            }
        }
    }
    cout << count00 * count01 * count10 * count11 << endl;
}
void addmod(int &x, int delta, int mod) {
    x += delta;
    x %= mod;
    if (x < 0) x += mod;
}

void move(pair<int,int> &pos, const pair<int,int> &speed,
          int width, int height)
{
    addmod(pos.first, speed.first, width);
    addmod(pos.second, speed.second, height);
}

pair<int,int> findPeriod(pair<int,int> pos, const pair<int,int> &speed,
                         int width, int height)
{
    map<pair<int,int>, int> when;
    when[pos] = 0;
    int steps = 0;
    while (true) {
        move(pos, speed, width, height);
        ++steps;
        if (auto it = when.find(pos); it == when.end())
            when[pos] = steps;
        else {
            return {it->second,  steps - it->second};
        }
    }
}

void part2() {
    string s;
    const int width = 101;
    const int height = 103;
    vector<pair<int,int>> pos, speed;    
    while (getline(cin, s)) {
        int x, y, vx, vy;
        int code = sscanf(s.c_str(), "p=%d,%d v=%d,%d", &x, &y, &vx, &vy);
        assert(code == 4);
        pos.emplace_back(x,y);
        speed.emplace_back(vx, vy);
        //auto [before, period] = findPeriod(pos.back(), speed.back(), width, height);
        //cout << "before = " << before << ", period = " << period << endl;
    }
    set<vector<string>> maps;
    map<vector<string>,int> when;
    auto solveFirstProblem = [&](){
        int64_t count[4]{};
        for (auto &[x, y] : pos) {
            if (x < width/2) {
                if (y < height/2) {
                    count[0]++;
                } else if (y > height/2) {
                    count[1]++;
                }
            } else if (x > width/2) {
                if (y < height/2) {
                    count[2]++;
                } else if (y > height/2) {
                    count[3]++;
                }
            }
        }
        cout << "answ = " << count[0] * count[1] * count[2] * count[3] << endl;
    };
    auto print = [&](int steps) -> bool {
        // создаём карту:
        vector<string> a(height, string(width, '.'));
        for (auto &[x,y] : pos)
            a[y][x] = 'X';
        if (!maps.insert(a).second)
            return false;
        when[a] = steps;
        return true;
    };
    auto move = [&]() {
        for (int i = 0; i < isz(pos); i++)
            ::move(pos[i], speed[i], width, height);
    };
    for (int step = 1; ; step++) {
        move();
        if (print(step))
            false && cout << "steps = " << step << endl;
        else
            break;
        if (step == 100) {
            solveFirstProblem();
        }
    }
    int numSym = 0;
    set<int> values;
    auto bestSizes = make_pair(vector<int>{}, vector<string>{});
    auto best = make_tuple(0, 0, vector<string>{});
    for (auto &a : maps) {
        // Ёлочка = фигура, образованная одной компонентой связности
        // скорее всего, в этой компонент большинство точек
        // давайте найдём такую карту, для которой самая большая компонента
        // максимальна. Скорее всего, это ёлочка - проверим визуально (на глаз)
        
        vector used(height, vector(width, false));
        vector<int> sizes;
        function<void(int,int)> dfs = [&](int y, int x) {
            if (y < 0 || y >= height) return;
            if (x < 0 || x >= width) return;
            if (used[y][x]) return;
            if (a[y][x] == '.') return;
            used[y][x] = 1;
            sizes.back()++;
            dfs(y,x-1);
            dfs(y,x+1);
            dfs(y-1,x);
            dfs(y+1,x);
        };
        int comp = 0;
        for (int y = 0; y < height; y++)
            for (int x = 0; x < width; x++)
                if (a[y][x] != '.') {
                    if (!used[y][x]) {
                        sizes.push_back(0);
                        dfs(y, x);
                        comp++;
                    }
                }
        sort(all(sizes), greater<>());
        bestSizes = max(bestSizes, make_pair(sizes, a));
    }
    const auto [sizes, a] = bestSizes;
    for (auto &s : a)
        cout << s << endl;
    cout << "answ2 = " << when[a] << endl;
}
main() {
    part2();
}

