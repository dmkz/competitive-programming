#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()

using namespace std;
using ll = long long;
using vi = vector<int>;

ll solve(vi a, int k) {
    sort(all(a));
    // мы не можем набрать больше, чем сумма всех / k:
    ll sum = accumulate(all(a), ll(0));
    ll best = sum / k;
    // вынимаем k-1 максимумов:
    vi maximums;
    for (int cnt = k-1; cnt--; ) {
        maximums.push_back(a.back());
        a.pop_back();
    }
    maximums.push_back(0);
    reverse(all(maximums));
    // будем тратить наши максимумы пока они не закончатся
    // а оставшиеся элементы набирать из мелких равномерно
    ll sumSmallPart = sum - accumulate(all(maximums), ll(0));
    ll answ = 0;
    for (int countDead = 1; countDead < k; countDead++) {
        // через сколько операций сдохнет текущий максимум:
        ll stepsToDie = maximums[countDead] - maximums[countDead-1];
        // через сколько операций закончатся мелкие элементы:
        ll stepsToEnd = sumSmallPart / countDead;
        // обновляем ответ:
        ll delta = std::min(stepsToDie, stepsToEnd);
        answ += delta;
        sumSmallPart -= delta * countDead;
    }
    // если остались мелкие элементы, то мы можем их равномерно поделить:
    if (sumSmallPart >= k)
        answ += (sumSmallPart / k);
    return min(best, answ);
}

int main() {
    int n, k;
    while (std::cin >> n >> k) {
        vi a(n); for (auto &it : a) std::cin >> it;
        std::cout << solve(a, k) << std::endl;
    }
}
