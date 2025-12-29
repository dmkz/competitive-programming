// жадные алгоритмы, сортировки, очередь с приоритетами, два указателя
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using ll = long long;
using pll = std::pair<ll,ll>;
using vl = std::vector<ll>;
using vi = std::vector<int>;
void solve() {
    // покупает подарок для каждого друга
    // i-му другу: стоимость >= y[i]
    // i-й друг счастлив: (красота коробки >= x[i]) || (стоимость >= z[i] > y[i])
    // у монокарпа k монет
    // вычитаем сумму y[i]:
    
    // i-му другу: стоимость >= 0
    // i-й друг счастлив: (красота коробки >= x[i]) || (стоимость >= z[i] - y[i])
    // у монокарпа k - SY монет
    
    // кого мы делаем счастливыми, а кого нет?
    // мы явно ходим потратить сумму всех y[i], проще вычесть сначала
    // далее мы можем либо доплатить z[i] - y[i],
    // либо подарить другу коробку! дарим коробки самым дорогим
    int n, m; ll k, answ{};
    std::cin >> n >> m >> k;
    vi box(m);
    for (int i = 0; i < isz(box); i++)
        std::cin >> box[i];
    std::sort(all(box));
    std::vector<std::tuple<int,int,int>> friends(n);
    for (auto &[x, y, z] : friends) {
        std::cin >> x >> y >> z;
        k -= y;
        z -= y;
        y -= y;
    }
    std::sort(all(friends));
    // для каждой коробки пикаем самого дорогого друга бесплатно
    std::priority_queue<pll> queue;
    {
        int i = 0;
        for (auto curr : box) {
            while (i < n && std::get<0>(friends[i]) <= curr) {
                auto [x,y,z] = friends[i];
                queue.push(pll(z, i));
                i++;
            }
            if (isz(queue)) {
                //auto [val, ind] = queue.top();
                queue.pop();
                answ++;
            }
        }
        // коробки кончились, кидаем друзей просто так
        while (i < n) {
            auto [x,y,z] = friends[i];
            queue.push(pll(z, i));
            i++;
        }
    }
    // остаток из очереди вынимаем и берём минимумы
    vl rem;
    while (isz(queue)) {
        auto [val, ind] = queue.top();
        queue.pop();
        rem.push_back(val);
    }
    for (int i = isz(rem)-1; i >= 0; i--)
        if (rem[i] <= k) {
            answ++;
            k -= rem[i];
        }
    std::cout << answ << "\n";
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0) solve();
}
