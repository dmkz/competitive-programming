#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
void setmax(auto &x, const auto &y) { if (x < y) x = y; }
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, t, zeros = 0; cin >> n >> t;
    vector<int> positive, negative;
    for (int i = 0, a; i < n; i++) {
        cin >> a;
        if (a > 0) positive.push_back(a);
        else if (a < 0) negative.push_back(a);
        else zeros++;
    }
    // мы либо идём удвоенные путь до какого-то положительного, а затем
    // возвращаемся в отрицательную зону, либо зеркальный вариант
    int answ = zeros;
    for (int swapped = 0; swapped < 2; swapped++) {
        for (int i = 0; i < isz(positive); i++) {
            int x = positive[i];
            // вариант 1: идём до x и останавливаемся:
            if (t >= x) setmax(answ, i+1+zeros);
            // идём 2 * x и затем пытаемся бинарным поиском определить
            // самую крайнюю отрицательную штуку до которой дойдём
            int rem = t - 2 * x;
            if (rem >= 0) {
                // low не можем, high - можем
                int low = -1, high = isz(negative);
                while (high - low > 1) {
                    int mid = (low + high) / 2;
                    if (abs(negative[mid]) <= rem) high = mid;
                    else low = mid;
                }
                // high - индекс самого крайнего, которого можем посетить
                setmax(answ, i+1+zeros+isz(negative)-high);
            }
        }
        // меняем местами положительные и отрицательные числа, меняя знак и порядок,
        // чтобы вызвать тот же самый код ещё один раз
        swap(positive, negative);
        for (auto &it : positive) it = -it;
        for (auto &it : negative) it = -it;
        reverse(all(positive));
        reverse(all(negative));
    }
    cout << answ << endl;
}
