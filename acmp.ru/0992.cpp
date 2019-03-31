/*
    Задача: 992. Неприводимые диаграммы Юнга
    
    Решение: математическое моделирование, O(sum)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define isz(x) (int)(x).size()
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    for (int n; std::cin >> n; ) {
        std::vector<int> arr(n+2);
        for (int i = 0; i < n; ++i) {
            std::cin >> arr[i];
        }
        for (int i = n-1; i >= 0; --i) {
            int delta = arr[i] - arr[i+1];
            arr[i] -= delta / 2 * 2;
            if (arr[i] == arr[i+1]) {
                delta = arr[i] - arr[i+2];
                arr[i] -= delta;
                arr[i+1] -= delta;
            }
        }
        while (!arr.empty() && arr.back() == 0) { arr.pop_back(); }
        if (arr.empty()) {
            std::cout << "1\n0\n";
            continue;
        }
        const int max = *std::max_element(all(arr));
        std::vector<int> cnt(max+1);
        for (auto it : arr) { cnt[it]++; }
        arr.clear();
        bool was = true;
        while (was) {
            was = false;
            for (int i = isz(cnt)-1; i >= 1; --i) {
                if (cnt[i] >= 2) {
                    was = true;
                    cnt[i-1] += cnt[i] / 2 * 2;
                    cnt[i] %= 2;
                    for (int j = i; j+1 < isz(cnt) && cnt[j] == 0; ++j) {
                        cnt[j-1] += cnt[j+1];
                        cnt[j+1] = 0;
                    }
                }
            }
            if (isz(cnt) > 0) { cnt[0] = 0; }
            while (!cnt.empty() && cnt.back() == 0) {
                cnt.pop_back();
            }
        }
        std::cout << 1 << "\n";
        for (int i = isz(cnt)-1; i >= 1; --i) {
            assert(cnt[i] == 1);
            arr.push_back(i);
        }
        std::cout << arr.size();
        for (auto it : arr) { std::cout << ' ' << it; }
        std::cout << '\n';
    }
    return 0;
}