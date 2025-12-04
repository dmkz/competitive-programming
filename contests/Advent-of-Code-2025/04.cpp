#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
void solveEasy() {
    std::string s;
    std::vector<std::string> a;
    while (std::getline(std::cin, s))
        a.push_back(s);
    const int nRows = isz(a);
    const int nCols = isz(a[0]);
    int answ{};
    for (int i = 0; i < nRows; i++)
        for (int j = 0; j < nCols; j++)
            if (a[i][j] == '@') {
                int curr = 0;
                for (int di = -1; di <= 1; di++)
                    for (int dj = -1; dj <= 1; dj++) {
                        if (di * di + dj * dj > 0) {
                            int ni = i + di, nj = j + dj;
                            if (ni < 0 || ni >= nRows) continue;
                            if (nj < 0 || nj >= nCols) continue;
                            curr += (a[ni][nj] == '@');
                        }
                    }
                answ += (curr < 4);
            }
    std::cout << answ << std::endl;
}
using pii = std::pair<int,int>;
using vpii = std::vector<pii>;
using spii = std::set<pii>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
void solveHard() {
    std::string s;
    std::vector<std::string> a;
    while (std::getline(std::cin, s))
        a.push_back(s);
    const int nRows = isz(a);
    const int nCols = isz(a[0]);
    int answ{};
    std::vector candidates(9, spii{});
    vvi weigth(nRows, vi(nCols));
    for (int i = 0; i < nRows; i++)
        for (int j = 0; j < nCols; j++)
            if (a[i][j] == '@') {
                int curr = 0;
                for (int di = -1; di <= 1; di++)
                    for (int dj = -1; dj <= 1; dj++)
                        if (di * di + dj * dj > 0) {
                            int ni = i + di, nj = j + dj;
                            if (ni < 0 || ni >= nRows) continue;
                            if (nj < 0 || nj >= nCols) continue;
                            curr += (a[ni][nj] == '@');
                        }
                weigth[i][j] = curr;
                candidates[curr].insert({i, j});
            }
    while (true) {
        // ищем кандидата на удаление:
        pii canRemove(-1, -1);
        for (int i = 0; i < 4; i++)
            if (isz(candidates[i]) > 0) {
                auto it = candidates[i].begin();
                canRemove = *it;
                candidates[i].erase(it);
                break;
            }
        if (canRemove.first == -1)
            break;
        auto [i, j] = canRemove;
        assert(a[i][j] == '@');
        a[i][j] = '.';
        answ++;
        for (int di = -1; di <= 1; di++)
            for (int dj = -1; dj <= 1; dj++)
                if (di * di + dj * dj > 0) {
                    int ni = i + di, nj = j + dj;
                    if (ni < 0 || ni >= nRows) continue;
                    if (nj < 0 || nj >= nCols) continue;
                    if (a[ni][nj] == '@') {
                        int prevW = weigth[ni][nj];
                        weigth[ni][nj]--;
                        int currW = weigth[ni][nj];
                        candidates[prevW].erase({ni, nj});
                        candidates[currW].insert({ni, nj});
                    }
                }
    }
    std::cout << answ << std::endl;
}
main() {
    solveHard();
}
