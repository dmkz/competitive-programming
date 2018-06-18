#include <stdio.h>
#include <vector>
#include <string>
#include <functional>
#include <cassert>
#include <cstdlib>
 
inline int prev(int p, int n) {
    return p == 0 ? n-1 : p-1;
}
 
inline int next(int p, int n) {
    return p == n-1 ? 0 : p+1;
}
 
std::string solve(const std::vector<int>& a) {
    const int n = a.size();
     
    // Считаем префикс-суммы:
    std::vector<int> pref{0};
    for (int i = 0; (int)pref.size() <= 2*n; i = next(i, n)) {
        pref.push_back(pref.back() + a[i]);
    }
    int sum = pref[n];
     
    // Обрабатываем особый случай:
    if (sum == 0) {
        return std::string(n, '1');
    }
     
    // Функция поиска разбиения массива на number отрезков с одинаковой суммой. Возвращает true, если такое разбиение существует.
    std::function<bool(int)> is_possible = [&](int number) {
        if (number == 1) {
            return true;
        }
         
        const int need = sum / number; // Нужная сумма каждого отрезка
        assert(need * number == sum);
         
        // Находим отрезок [0, r] такой, что sum[0,r] <= need, sum[0,r+1] > need 
        int l = 0, r = -1, curr = 0; 
        while (curr + a[next(r,n)] <= need) {
            curr += a[next(r,n)];
            r = next(r,n);
        }
         
        // Сдвигаем отрезок [l, r], получая все возможные отрезки, на которых сумма равна need и которые содержат нулевой элемент:
        while (r >= 0) { 
            // Сдвигаем левую границу пока не накопили нужную сумму:
            while (curr + a[prev(l,n)] <= need) { 
                curr += a[prev(l,n)];
                l = prev(l,n);
            }
            if (curr == need) { 
                // Пробуем построить еще number-1 отрезков, сумма на которых равна need:
                int low = r+1, prev = r, count = number-1;
                while (count > 0) {
                    if (pref[low+1] - pref[low] > need) {
                        break;
                    }
                    // [low, high)
                    int high = l == 0 ? n : l;
                    while (high-low > 1) {
                        int mid = (low + high) / 2;
                        if (pref[mid+1] - pref[prev+1] > need) {
                            high = mid;
                        } else {
                            low = mid;
                        }
                    }
                    if (pref[low+1]-pref[prev+1] == need) {
                        --count;
                        prev = low++;
                    } else {
                        break;
                    }
                }
                if (count == 0) {
                    return true;
                }
            }
            // Сдвигаем правую границу:
            curr -= a[r];
            --r;
        }
        return false;
    };
      
    std::string answ(n, '0');
    // Перебираем все делители суммы элементов массива:
    for (int i = 1; i * i <= sum; ++i) {
        const int j = sum / i;
        if (j * i == sum) {
            if (i <= n) {
                assert(answ[i-1] == '0');
                answ[i-1] += is_possible(i);
            }
            if (j <= n && j != i) {
                assert(answ[j-1] == '0');
                answ[j-1] += is_possible(j);
            }
        }
    }
    assert(answ[0] == '1');
    return answ;
}
 
int main() {
    int n;
    scanf("%d", &n);
    std::vector<int> a(n);
    for (auto& it : a) {
        scanf("%d", &it);
    }
    printf("%s\n", solve(a).c_str());
    return 0;
}