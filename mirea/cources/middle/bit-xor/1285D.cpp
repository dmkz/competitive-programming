#include <bits/stdc++.h>
int main() {
    int n; std::cin >> n;
    std::vector<int> a(n);
    for (auto &it : a)
        std::cin >> it;
    std::sort(a.begin(), a.end());
    std::function<int(int,int,int)> getMin = [&](int bit, int L, int R) {
        if (bit < 0)
            return 0;
        int low = L - 1, high = R + 1;
        while (high - low > 1) {
            int mid = (low + high) / 2;
            if ((a[mid] >> bit) & 1) high = mid;
            else low = mid;
        }
        // [L, low] состоит из 0, а [high, R] состоит из единиц
        if (low < L || high > R) // отрезок целиком из 0 или 1
            return getMin(bit-1,L,R);
        // иначе есть как нули, так и единицы
        return (1 << bit) | std::min(getMin(bit-1,L,low), getMin(bit-1,high,R));
    };
    std::cout << getMin(29, 0, (int)a.size()-1) << std::endl;
    return 0;
}
