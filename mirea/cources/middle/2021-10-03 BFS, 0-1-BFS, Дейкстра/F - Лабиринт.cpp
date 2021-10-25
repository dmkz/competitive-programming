#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;
const pii UNDEF{-1,-1};
int main() {
    // читаем все исходные данные:
    ios::sync_with_stdio(false);
    cin.tie(0);
    int nRows, nCols;
    cin >> nRows >> nCols;
    int sr, sc, nL, nR;
    cin >> sr >> sc >> nL >> nR;
    vector<string> field(1+nRows+1, string(1+nCols+1, '*'));
    for (int r = 1; r <= nRows; ++r) {
        for (int c = 1; c <= nCols; ++c) {
            cin >> field[r][c];
        }
    }
    // запускаем 0-1-bfs по числу поворотов:
    vector<vector<pii>> dist(1+nRows+1, vector<pii>(1+nCols+1, UNDEF));
    deque<pii> deque;
    deque.push_back({sr,sc}); // добавляем стартовую вершину
    dist[sr][sc] = {nL, nR};
    while (!deque.empty()) {
        // вынимаем текущую вершину:
        auto [r,c] = deque.front();
        deque.pop_front();
        // переход по рёбрам веса 0 - добавляем в начало дека:
        for (int dr : {-1,+1}) {
            if (field[r+dr][c] != '*' && dist[r+dr][c] == UNDEF) {
                dist[r+dr][c] = dist[r][c];
                deque.push_front({r+dr,c});
            }
        }
        // переход по рёбрам веса 1 - добавляем в конец дека (если поворот можно сделать):
        for (int dc : {-1,+1}) {
            if (field[r][c+dc] != '*' && dist[r][c+dc] == UNDEF) {
                auto [remL,remR] = dist[r][c];
                if (dc == -1) remL--;
                if (dc == +1) remR--;
                if (remL >= 0 && remR >= 0) {
                    dist[r][c+dc] = {remL,remR};
                    deque.push_back({r,c+dc});
                }
            }
        }
    }
    // считаем количество посещенных клеток и выводим его:
    int cnt = 0;
    for (int r = 1; r <= nRows; ++r) {
        for (int c = 1; c <= nCols; ++c) {
            cnt += !(dist[r][c] == UNDEF);
        }
    }
    cout << cnt << endl;
    return 0;
}