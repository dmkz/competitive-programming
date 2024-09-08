#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using ll = long long;
bool getbit(int mask, int i) { return (mask >> i) & 1; }

std::pair<ll,ll> solve(ll a, ll b, ll c, ll d)
{
    std::string sa = std::to_string(a);
    std::string sb = std::to_string(b);
    // нельзя лидирующие нули
    for (int mask = 0; mask + 1 < (1 << isz(sa)); mask++) {
        // перебираем позиции удалённых символов в "a"
        std::string na, removed;
        for (int i = 0; i < isz(sa); i++) {
            if (getbit(mask, i) == 0) {
                na += sa[i];
            } else {
                removed += sa[i];
            }
        }
        std::sort(all(removed));
        // лидирующие нули запрещены
        assert(isz(na));
        if (na.front() == '0')
            continue;
        // мы можем узнать какой знаменатель хотим
        __int128 temp = std::stoll(na) * __int128(d);
        if (temp % c != 0)
            continue;
        temp /= c;
        if (temp > b)
            continue;
        // знаем знаменатель
        // он должен быть подпоследовательностью числа b
        // а оставшиеся числа мы удаляем
        ll nb = ll(temp);
        // находим nb как подпоследовательность в b
        std::string snb = std::to_string(nb);
        std::string needToRemove;
        int j = 0;
        for (int i = 0; i < isz(sb); i++) {
            if (j < isz(snb) && sb[i] == snb[j]) {
                j++;
            } else {
                needToRemove += sb[i];
            }
        }
        std::sort(all(needToRemove));
        // если нашли подпоследовательность и остальные символы удалены
        // то нашли ответ
        if (j == isz(snb) && needToRemove == removed) {
            return {std::stoll(na), nb};
        }
    }
    return {-1,-1};
}
main() {
    ll a, b, c, d;
    std::cin >> a >> b >> c >> d;
    auto [na,nb] = solve(a,b,c,d);
    if (na != -1) {
        std::cout << "possible\n";
        std::cout << na << " " << nb << std::endl;
    } else {
        std::cout << "impossible\n";
    }
}
