#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using namespace std;
const int up = 0, right = 1, down = 2, left = 3;
const int deltaR[] = {-1,0,+1,0};
const int deltaC[] = {0,+1,0,-1};
void part1() {
    int64_t answ{};
    string s;
    vector<string> a;
    while (getline(cin, s)) {
        a.push_back(s);
    }
    const int nRows = (int)a.size();
    const int nCols = (int)a[0].size();
    int sr=-1, sc=-1, dir=-1;
    for (int r = 0; dir == -1 && r < nRows; r++)
        for (int c = 0; c < nCols; c++)
            if (a[r][c] == '^') {
                sr = r;
                sc = c;
                dir = up;
                a[r][c] = '.';
                break;
            }
    assert(dir != -1);
    vector visited(nRows, vector<bool>(nCols));
    visited[sr][sc] = 1;
    while (true) {
        int nr = sr + deltaR[dir];
        int nc = sc + deltaC[dir];
        if (nr < 0 || nr >= nRows ||
            nc < 0 || nc >= nCols)
            break;
        if (a[nr][nc] == '#') {
            dir = (dir + 1) % 4;
            continue;
        }
        sr = nr;
        sc = nc;
        visited[sr][sc] = 1;
    }
    for (int r = 0; r < nRows; r++)
        for (int c = 0; c < nCols; c++)
            answ += visited[r][c];
    cout << answ << endl;
}

void part2() {
    int64_t answ{};
    string s;
    vector<string> a;
    while (getline(cin, s)) {
        a.push_back(s);
    }
    const int nRows = (int)a.size();
    const int nCols = (int)a[0].size();
    int sr=-1, sc=-1, dir=-1;
    for (int r = 0; dir == -1 && r < nRows; r++)
        for (int c = 0; c < nCols; c++)
            if (a[r][c] == '^') {
                sr = r;
                sc = c;
                dir = up;
                a[r][c] = '.';
                break;
            }
    assert(dir != -1);
    cout << "cells: " << nRows * nCols << endl;
    for (int r = 0; r < nRows; r++)
        for (int c = 0; c < nCols; c++)
            if (!(r == sr && c == sc) && a[r][c] == '.') {
                a[r][c] = '#';
                // проверить что цикл
                int currRow = sr;
                int currCol = sc;
                dir = up;
                int steps = 0;
                while (steps < 20000) {
                    int nr = currRow + deltaR[dir];
                    int nc = currCol + deltaC[dir];
                    if (nr < 0 || nr >= nRows ||
                        nc < 0 || nc >= nCols)
                        break;
                    if (a[nr][nc] == '#') {
                        dir = (dir + 1) % 4;
                        continue;
                    }
                    currRow = nr;
                    currCol = nc;
                    steps++;
                }
                answ += (steps == 20000);
                a[r][c] = '.';
            }
    cout << answ << endl;
}
main() {
    part2();
}
