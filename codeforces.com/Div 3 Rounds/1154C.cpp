/*
    problem: 1154C. Gourmet Cat
    solution: binary search by the answer, math
*/
#include "template.hpp"
int main() {
    // week: [a b c a c b a]
    ll a,b,c; std::cin >> a >> b >> c;
    auto checkWithFixedDay = [&](ll startDay, ll days) {
        // начинаем в заданный день и пытаемся продержаться данное количество дней
        vl need(7);
        const ll rem = days % 7;
        for (ll r = 0; r < rem; r++)
            need[(startDay+r)%7]=(days+6)/7;
        for (ll r = rem; r < 7; r++)
            need[(startDay+r)%7]=days/7;
        assert(std::accumulate(all(need), ll(0)) == days);
        bool res = (need[0] + need[3] + need[6] <= a) &&
               (need[1] + need[5] <= b) &&
               (need[2] + need[4] <= c);
        return res;
    };
    auto check = [&](ll days) {
        // знаем, что надо продержаться `days` дней
        for (int startDay = 0; startDay < 7; startDay++)
            if (checkWithFixedDay(startDay, days))
                return true;
        return false;
    };
    
    ll low = -1, high = 1e12+1;
    while (high - low > 1) {
        ll mid = (low + high) / 2;
        if (check(mid)) low = mid;
        else high = mid;
    }
    std::cout << low << std::endl;
    return 0;
}
