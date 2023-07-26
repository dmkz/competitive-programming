/*
    problem: 1092C. Prefixes and Suffixes
    solution: string, prefix, suffix
*/
#include "template.hpp"
#include "debug.hpp"
std::string check(const vs &a, std::string s) {
    std::map<std::string, vi> indexes;
    for (int i = 0; i < isz(a); i++)
        indexes[a[i]] << i;
    std::string answer(isz(a), '?');
    for (int len = 1; len < isz(s); len++)
        for (char ch = 'P'; auto t : {s.substr(0, len), s.substr(isz(s)-len,len)})
        {
            if (auto &it = indexes[t]; isz(it))
                answer[it--] = ch;
            else
                return "";
            ch = 'S';
        }
    return answer;
}
int main() {
    int tt = 1; // std::cin >> tt;
    while (tt --> 0) {
        int n; std::cin >> n;
        vs a(2*n-2);
        std::cin >> a;
        std::string fi, se;
        for (auto &it : a)
        {
            if (isz(it) == n-1)
            {
                if (fi.empty())
                    fi = it;
                else
                {
                    assert(se.empty());
                    se = it;
                }
            }
        }
        std::string cand1 = fi + se.back();
        std::string cand2 = se + fi.back();
        bool was = 0;
        for (auto it : {cand1, cand2})
        {
            auto res = check(a, it);
            if (isz(res)) {
                was = 1;
                std::cout << res << "\n";
                break;
            }
        }
        assert(was);
    }
}
