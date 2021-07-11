#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using ld = long double;
int main() {
    std::cout << std::setprecision(24);
    int n; std::cin >> n;
    std::vector<int> v(n);
    for (auto &it : v) std::cin >> it;
    std::priority_queue<ld,std::vector<ld>,std::greater<ld>> pq;
    for (auto it : v) pq.push(it);
    // нам выгодно вынимать два минимальных элемента, считать их среднее и возвращать обратно
    // потому что каждой вычисление среднего умножает несколько чисел на 0.5 в итоговой сумме:
    // w1 * a1 + w2 * a2 + ... + wn * an
    // пусть a - посорчены, тогда нужно wn сделать как можно меньше, значит используем его в конце ровно 1 раз (меньше не можем)
    // a[n-1] два раза (меньше не можем)
    // a[n-2] три раза (меньше не можем)
    // ... и т.д.
    while (isz(pq) >= 2) {
        auto x = pq.top(); pq.pop();
        auto y = pq.top(); pq.pop();
        pq.push((x+y)/2);
    }
    std::cout << pq.top() << std::endl;
    return 0;
}