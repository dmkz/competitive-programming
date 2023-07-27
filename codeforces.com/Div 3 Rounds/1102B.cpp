/*
    problem: 1102B. Array K-Coloring
    solution: implementation, positions of items, grouping
*/
#include "template.hpp"
int main() {
    int n, k; std::cin >> n >> k;
    std::map<int, vi> items;
    for (int i = 0, a; i < n; i++) {
        std::cin >> a;
        items[a] << i;
    }
    int mxLen = 0;
    for (auto &[_, poses] : items)
        remax(mxLen, isz(poses));
    if (mxLen > k) {
        std::cout << "NO\n";
        return 0;
    }
    vi answ(n);
    std::map<int, vi> posByColor;
    for (int id = 1; id <= mxLen; id++)
        for (auto &[_, poses] : items)
            if (isz(poses)) {
                int pos = poses--;
                answ[pos] = id;
                posByColor[id] << pos;
            }
    // могло так получиться, что какие-то цвета [mxLen+1, ..., k] оказались не использованы
    // надо это исправить
    for (auto &[_, poses] : posByColor)
        for (int i = 1; i < isz(poses); i++)
            if (mxLen < k) {
                int pos = poses[i];
                answ[pos] = ++mxLen;
            }
    std::cout << "YES\n";
    for (auto it : answ)
        std::cout << it << ' ';
}
