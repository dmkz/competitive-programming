#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using namespace std;
using pii = pair<int,int>;
using vpii = vector<pii>;
string path2str(vpii path) {
    string s;
    for (int i = 0; i < isz(path); i++) {
        if (i > 0) {
            s += " -> ";
        }
        auto [x,y] = path[i];
        s += to_string(x);
        s += ',';
        s += to_string(y);
    }
    return s;
}
int sign(int x) {
    if (x < 0) return -1;
    if (x > 0) return +1;
    return 0;
}

void part1() {
    map<pii,char> a;
    auto getCell = [&a](int x, int y) -> char& {
        auto it = a.find({x,y});
        if (a.end() == it)
            return a[{x,y}] = '.';
        return a[{x,y}];
    };
    string s;
    while(getline(cin,s)) {
        istringstream ss(s);
        char c;
        int x, y;
        vpii path;
        while (ss >> x >> c >> y) {
            path.emplace_back(x, y);
            ss >> c >> c;
        }
        auto t = path2str(path);
        if (t != s) {
            std::cout << "s = '" << s << "'" << std::endl;
            std::cout << "t = '" << t << "'" << std::endl;
        }
        assert(t == s);
        for (int i = 0; i + 1 < isz(path); i++) {
            auto [x0, y0] = path[i];
            auto [x1, y1] = path[i+1];
            const int dx = sign(x1 - x0), dy = sign(y1 - y0);
            getCell(x1,y1) = '#';
            while (!(x0 == x1 && y0 == y1)) {
                getCell(x0,y0) = '#';
                x0 += dx, y0 += dy;
            }
        }
    }
    
    function<bool(int,int,int)> dfs = [&](int x, int y, int limit) -> bool {
        if (limit <= 0) return false;
        //cout << "dfs(" << x << "," << y << ")" << endl;
        if (getCell(x,y+1) == '.') return dfs(x, y+1,limit-1);
        else if (getCell(x-1,y+1) == '.') return dfs(x-1, y+1, limit-1);
        else if (getCell(x+1,y+1) == '.') return dfs(x+1, y+1, limit-1);
        else {
            getCell(x,y) = 'o';
            return true;
        }
    };
    auto printTable = [&](int yMin, int yMax, int xMin, int xMax) {
        cout << "table:\n";
        for (int y = yMin; y <= yMax; y++) {
            for (int x = xMin; x <= xMax; x++)
                cout << getCell(x,y);
            cout << endl;
        }
    };
    //printTable(0, 9, 493, 504);
    int cnt = 0;
    for (; dfs(500,0,10000); cnt++) /*printTable(0, 9, 493, 504)*/;
    cout << cnt << endl;
}
void part2() {
    map<pii,char> a;
    auto getCell = [&a](int x, int y) -> char& {
        auto it = a.find({x,y});
        if (a.end() == it)
            return a[{x,y}] = '.';
        return a[{x,y}];
    };
    auto putPath = [&](const vpii &path) {
        for (int i = 0; i + 1 < isz(path); i++) {
            auto [x0, y0] = path[i];
            auto [x1, y1] = path[i+1];
            const int dx = sign(x1 - x0), dy = sign(y1 - y0);
            getCell(x1,y1) = '#';
            while (!(x0 == x1 && y0 == y1)) {
                getCell(x0,y0) = '#';
                x0 += dx, y0 += dy;
            }
        }
    };
    string s;
    int yMax = 0;
    while(getline(cin,s)) {
        istringstream ss(s);
        char c;
        int x, y;
        vpii path;
        while (ss >> x >> c >> y) {
            path.emplace_back(x, y);
            ss >> c >> c;
            if(yMax < y) yMax = y;
        }
        auto t = path2str(path);
        if (t != s) {
            std::cout << "s = '" << s << "'" << std::endl;
            std::cout << "t = '" << t << "'" << std::endl;
        }
        assert(t == s);
        putPath(path);
    }
    putPath({{-10000,yMax+2},{10000,yMax+2}});
    function<bool(int,int,int)> dfs = [&](int x, int y, int limit) -> bool {
        if (limit <= 0) return false;
        //cout << "dfs(" << x << "," << y << ")" << endl;
        if (getCell(x,y+1) == '.') return dfs(x, y+1,limit-1);
        else if (getCell(x-1,y+1) == '.') return dfs(x-1, y+1, limit-1);
        else if (getCell(x+1,y+1) == '.') return dfs(x+1, y+1, limit-1);
        else {
            getCell(x,y) = 'o';
            return true;
        }
    };
    auto printTable = [&](int yMin, int yMax, int xMin, int xMax) {
        cout << "table:\n";
        for (int y = yMin; y <= yMax; y++) {
            for (int x = xMin; x <= xMax; x++)
                cout << getCell(x,y);
            cout << endl;
        }
    };
    //printTable(0, 9, 493, 504);
    int cnt = 0;
    while (getCell(500,0) != 'o') {
        bool res = dfs(500, 0, 10000);
        assert(res);
        cnt++;
    }
    cout << cnt << endl;
}
int main() {
    part2();
}