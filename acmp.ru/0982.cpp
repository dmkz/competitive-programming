/*
    Задача: 982. Шашки - 3
    
    Решение: графы, поиск в глубину, шахматная доска, O(n^4)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <set>
#include <map>

typedef std::vector<std::string> vs;
typedef std::vector<bool> vb;
typedef std::vector<vb> vvb;

int main() {
    vs field(8);
    for (int i = 0; i < 8; ++i) {
        std::cin >> field[i];
    }
    typedef std::pair<int,int> pii;
    std::map<std::string, std::set<pii>> answ;
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            if (field[r][c] == '.') { continue; }
            vvb visited(8, vb(8, false));
            std::function<void(int,int)> visit = [&](const int row, const int col) {
                if (visited[row][col]) return;
                visited[row][col] = true;
                for (int dr = -2; dr <= 2; ++dr) {
                    for (int dc = -2; dc <= 2; ++dc) {
                        if (dr * dr + dc * dc != 8) { continue; }
                        int nr = row + dr;
                        int nc = col + dc;
                        int mr = row + dr / 2;
                        int mc = col + dc / 2;
                        if (nr < 0 || nr >= 8 || nc < 0 || nc >= 8) { continue; }
                        if (field[nr][nc] != '.') { continue; }
                        if (field[mr][mc] == 'W' + 'B' - field[r][c]) {
                            answ[field[r][c] == 'W' ? "White" : "Black"].insert(pii(mr+1, mc+1));
                            visit(nr, nc);
                        }
                    }
                }
            };
            visit(r,c);
        }
    }
    for (auto team : vs{"White", "Black"}) {
        printf("%s: %d\n", team.c_str(), (int)answ[team].size());
        std::string out;
        for (auto p : answ[team]) {
            out += "(" + std::to_string(p.first) + ", " + std::to_string(p.second) + "), ";
        }
        if (!out.empty()) {
            out.pop_back();
            out.pop_back();
            std::cout << out << std::endl;
        }
    }
    return 0;
}