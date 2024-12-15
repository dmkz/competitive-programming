#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using namespace std;
const string dirs = "^>v<";
const int dr[] = {-1,0,+1,0};
const int dc[] = {0,+1,0,-1};
int findDir(char c) {
    int res = (int)dirs.find(c);
    assert(res != -1);
    return res;
}
void part1() {
    string s;
    vector<string> a;
    while (getline(cin, s)) {
        if (s.empty()) break;
        a.push_back(s);
    }
    s = "";
    for (string ss; getline(cin, ss); s += ss);
    int r = -1, c = -1;
    for (int i = 0; i < isz(a); i++)
        for (int j = 0; j < isz(a[i]); j++)
            if (a[i][j] == '@') {
                r = i, c = j;
                a[i][j] = '.';
            }
    assert(r != -1 && c != -1);
    for (int i = 0; i < isz(s); i++) {
        int dir = findDir(s[i]);
        int nr = r + dr[dir], nc = c + dc[dir];
        if (a[nr][nc] == '.') {
            r = nr, c = nc;
        } else if (a[nr][nc] == '#') {
            // ничего
        } else {
            assert(a[nr][nc] == 'O');
            int boxR = nr, boxC = nc;
            while (a[boxR][boxC] == 'O') {
                boxR += dr[dir];
                boxC += dc[dir];
            }
            if (a[boxR][boxC] == '#')
                continue;
            assert(a[boxR][boxC] == '.');
            a[boxR][boxC] = 'O';
            a[nr][nc] = '.';
            r = nr, c = nc;
        }
    }
    int64_t answ{};
    for (int i = 0; i < isz(a); i++)
        for (int j = 0; j < isz(a[i]); j++)
            if (a[i][j] == 'O') {
                answ += 100 * i + j;
            }
    cout << answ << endl;
}

void part2() {
    // чтение поля:
    string s;
    vector<string> a;
    vector<pair<int,int>> boxes;
    vector<vector<int>> boxId;
    int robotR = -1, robotC = -1;
    for (int r = 0; getline(cin, s); r++) {
        if (s.empty()) break;
        boxId.push_back({});
        string t;
        for (auto ch : s) {
            switch (ch) {
                case '#': {
                    t += "##";
                    boxId.back().insert(boxId.back().end(), {-1,-1});
                    break;
                }
                case 'O': {
                    t += "[]";
                    const int c = isz(t)-2;
                    boxes.emplace_back(r, c);
                    int id = isz(boxes)-1;
                    boxId.back().insert(boxId.back().end(), {id, id});
                    break;
                }
                case '.': {
                    t += "..";
                    boxId.back().insert(boxId.back().end(), {-1,-1});
                    break;
                }
                case '@': {
                    t += "..";
                    robotR = r, robotC = isz(t)-2;
                    boxId.back().insert(boxId.back().end(), {-1,-1});
                    break;
                }
            };
        }
        a.push_back(t);
    }
    assert(robotR != -1 && robotC != -1);
    // чтение команд:
    s = "";
    for (string ss; getline(cin, ss); s += ss);
    // функция dfs поиском в глубину находим множество коробок, которые
    // будут сдвинуты по направлению dir. Возвращает, есть ли стена
    set<int> subset;
    function<bool(int,int,int)> dfs = [&](int r, int c, int dir) -> bool
    {
        if (boxId[r][c] == -1)
            return (a[r][c] == '#');
        int id = boxId[r][c];
        if (!subset.insert(id).second)
            return false;
        auto [boxR, boxC] = boxes[id];
        bool firstWall = dfs(boxR+dr[dir], boxC+dc[dir],dir);
        bool secondWall = dfs(boxR+dr[dir], boxC+1+dc[dir],dir);
        return firstWall || secondWall;
    };
    auto clearMapForSubset = [&](){
        for (int id : subset) {
            auto [boxR, boxC] = boxes[id];
            const char boxChars[] = "[]";
            for (int delta = 0; delta <= 1; delta++) {
                assert(boxId[boxR][boxC+delta] == id);
                boxId[boxR][boxC+delta] = -1;
                assert(a[boxR][boxC+delta] == boxChars[delta]);
                a[boxR][boxC+delta] = '.';
            }
        }
    };
    auto assignMapForSubset = [&](){
        for (int id : subset) {
            auto [boxR, boxC] = boxes[id];
            const char boxChars[] = "[]";
            for (int delta = 0; delta <= 1; delta++) {
                assert(boxId[boxR][boxC+delta] == -1);
                boxId[boxR][boxC+delta] = id;
                assert(a[boxR][boxC+delta] == '.');
                a[boxR][boxC+delta] = boxChars[delta];
            }
        }
    };
    auto moveSubset = [&](int dir){
        clearMapForSubset();
        for (int id : subset) {
            auto &[boxR, boxC] = boxes[id];
            boxR += dr[dir];
            boxC += dc[dir];
        }
        assignMapForSubset();
    };
    // решаем задачку:
    for (int i = 0; i < isz(s); i++) {
        int dir = findDir(s[i]);
        int nr = robotR + dr[dir], nc = robotC + dc[dir];
        if (a[nr][nc] == '.') {
            robotR = nr, robotC = nc;
        } else if (a[nr][nc] == '#') {
            // ничего
        } else {
            assert(a[nr][nc] == '[' || a[nr][nc] == ']');
            subset.clear();
            bool thereIsAWall = dfs(nr, nc, dir);
            if (thereIsAWall) continue;
            robotR = nr;
            robotC = nc;
            moveSubset(dir);
        }
    }
    int64_t answ{};
    for (int i = 0; i < isz(a); i++)
        for (int j = 0; j < isz(a[i]); j++)
            if (a[i][j] == '[') {
                answ += 100 * i + j;
            }
    cout << answ << endl;
}
main() {
    part2();
}

