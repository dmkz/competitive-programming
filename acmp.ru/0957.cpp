/*
    Задача: 957. Доказательство в HOL
    
    Решение: рекурсия, конструктив, O(4^n * n)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <cassert>

const int LU = 0, LD = 1, RU = 2, RD = 3;

int erow, ecol, n, cnt;
std::vector<std::vector<int>> arr;

void set(int r, int c, int val) {
    assert(arr[r][c] == -1);
    arr[r][c] = val;
}

void fill(int r, int c, int side, int type) {
    assert(side >= 2);
    if (side == 2) {
        ++cnt;
        if (type == LU) {
            set(r,c,cnt);
            set(r+1,c,cnt);
            set(r,c+1,cnt);
        } else if (type == LD) {
            set(r,c,cnt);
            set(r+1,c,cnt);
            set(r+1,c+1,cnt);
        } else if (type == RU) {
            set(r,c,cnt);
            set(r,c+1,cnt);
            set(r+1,c+1,cnt);
        } else if (type == RD) {
            set(r+1,c,cnt);
            set(r,c+1,cnt);
            set(r+1,c+1,cnt);
        }
        return;
    }
    
    if (type == RD) {
        fill(r, c+side/2, side/2, RU);
        fill(r+side/2, c, side/2, LD);
        fill(r+side/2,c+side/2,side/2, RD);
        fill(r+side/4,c+side/4,side/2, RD);
    } else if (type == RU) {
        fill(r,c,side/2,LU);
        fill(r,c+side/2,side/2,RU);
        fill(r+side/2,c+side/2,side/2,RD);
        fill(r+side/4,c+side/4,side/2,RU);
    } else if (type == LD) {
        fill(r,c,side/2,LU);
        fill(r+side/2,c,side/2,LD);
        fill(r+side/2,c+side/2,side/2,RD);
        fill(r+side/4,c+side/4,side/2,LD);
    } else if (type == LU) {
        fill(r,c+side/2,side/2,RU);
        fill(r+side/2,c,side/2,LD);
        fill(r,c,side/2,LU);
        fill(r+side/4,c+side/4,side/2,LU);
    }
}

void solve(int r, int c, int side) {
    assert(side >= 2);
    if (side == 2) {
        cnt++;
        for (int i = r; i < r + side; ++i) {
            for (int j = c; j < c + side; ++j) {
                if (i == erow && j == ecol) continue;
                set(i,j,cnt);
            }
        }
        return;
    }
    if (erow < r + side / 2 && ecol < c + side / 2) {
        solve(r, c, side / 2);
        fill(r, c+side/2, side/2, RU);
        fill(r+side/2, c, side/2, LD);
        fill(r+side/2,c+side/2,side/2, RD);
        fill(r+side/4,c+side/4,side/2, RD);
    } else if (erow >= r + side / 2 && ecol < c + side / 2) {
        solve(r+side/2,c,side/2);
        fill(r,c,side/2,LU);
        fill(r,c+side/2,side/2,RU);
        fill(r+side/2,c+side/2,side/2,RD);
        fill(r+side/4,c+side/4,side/2,RU);
    } else if (erow < r + side/2 && ecol >= c + side/2) {
        solve(r,c+side/2,side/2);
        fill(r,c,side/2,LU);
        fill(r+side/2,c,side/2,LD);
        fill(r+side/2,c+side/2,side/2,RD);
        fill(r+side/4,c+side/4,side/2,LD);
    } else if (erow >= r+side/2 && ecol >= c + side/2) {
        solve(r+side/2,c+side/2,side/2);
        fill(r,c+side/2,side/2,RU);
        fill(r+side/2,c,side/2,LD);
        fill(r,c,side/2,LU);
        fill(r+side/4,c+side/4,side/2,LU);
    }
}

int main() {
    scanf("%d %d %d", &n, &ecol, &erow);
    ecol--,erow--;
    arr.assign(1 << n, std::vector<int>(1 << n, -1));
    arr[erow][ecol] = 0;
    solve(0, 0, 1 << n);
    for (auto& row : arr) {
        for (auto& it : row) {
            std::cout << it << ' ';
        }
        std::cout << std::endl;
    }
    return 0;
}