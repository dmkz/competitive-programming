/*
    Problem: 368B. Sereja and Suffixes
    Solution: queries offline, sorting, O(n + q log(q))
*/
#include <bits/stdc++.h>
typedef std::pair<int,int> pii;
int main() {
    for (int n, q; std::cin >> n >> q;) {
        std::vector<int> a(n), answ(q);
        for (auto &it : a) std::cin >> it;
        std::set<int> set;
        std::vector<pii> queries(q);
        for (int i = 0; i < q; i++) {
            int left; std::cin >> left;
            queries[i] = {left-1, i};
        }
        std::sort(queries.begin(), queries.end(),[](auto lt, auto rt) { return lt.first > rt.first; });
        int pos = n;
        for (auto & curr : queries) {
            while (pos > curr.first) {
                set.insert(a[--pos]);
            }
            answ[curr.second] = (int)set.size();
        }
        for (auto & it : answ) std::cout << it << '\n';
        std::cout << std::endl;
    }
}