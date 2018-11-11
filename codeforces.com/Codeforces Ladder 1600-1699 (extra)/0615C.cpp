/*
    Problem: 615C. Running Track
    
    Solution: greedy, dynamic programming, longest common substring, O(n*m)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

struct Pair { int x, y; };

int main() {
    std::string s, t;
    while (std::cin >> s >> t) {
        const int n = (int)s.size(), m = (int)t.size();
        auto r = s;
        std::reverse(r.begin(), r.end());
        vvi maxLenS(n+1, vi(m+1)), maxLenR(n+1, vi(m+1));
        for (int i = n-1; i >= 0; --i) {
            for (int j = m-1; j >= 0; --j) {
                maxLenS[i][j] = (s[i] == t[j]) ? maxLenS[i+1][j+1]+1 : 0;
                maxLenR[i][j] = (r[i] == t[j]) ? maxLenR[i+1][j+1]+1 : 0;
            }
        }
        std::vector<Pair> answer;
        for (int i = 0; i < m; ) {
            int pmax = -1, tmax = -1, vmax = 0;
            for (int j = 0; j < n; ++j) {
                if (maxLenS[j][i] > vmax) {
                    vmax = maxLenS[j][i];
                    pmax = j;
                    tmax = 0;
                }
                if (maxLenR[j][i] > vmax) {
                    vmax = maxLenR[j][i];
                    pmax = j;
                    tmax = 1;
                }
            }
            if (vmax == 0) {
                answer.clear();
                break;
            }
            if (tmax == 0) {
                answer.push_back(Pair{pmax+1, pmax+vmax});
            } else {
                int x = pmax+1, y = pmax+vmax;
                x = n - x + 1;
                y = n - y + 1;
                answer.push_back(Pair{x, y});
            }
            i += vmax;
        }
        if (answer.empty()) {
            std::cout << -1 << std::endl;
        } else {
            std::cout << answer.size() << "\n";
            for (auto p : answer) {
                std::cout << p.x << ' ' << p.y << '\n';
            }
        }
    }
    return 0;
}