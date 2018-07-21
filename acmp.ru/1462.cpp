/*
    Задача: 1462. Силовые поля
    
    Решение: сортировка, stack, set, структуры данных, O(n log(n))
    
    Автор: Дмитрий Козырев, https://github.com/dmkz , dmkozyrev@rambler.ru
    
    Отсортируем по `x` и `y`. 
    Очевидно, что сторона искомого прямоугольника совпадет со стороной какого-то заданного прямоугольника.
    Переберем все стороны y, поддерживая множество кандидатов среди `x`, у которых `y` >= текущего `y`.
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

typedef long long ll;

struct Pair {
	int x, y;
};

int main() {	
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
	
	int n, limit; std::cin >> n >> limit;
	
	auto cmpx = [](const Pair& a, const Pair& b){
		return a.x < b.x || (a.x == b.x && a.y < b.y);
	};
	
	auto cmpy = [](const Pair& a, const Pair& b){
		return a.y < b.y || (a.y == b.y && a.x < b.x);
	};
	
	std::vector<Pair> ordered_x, ordered_y;
	for (int i = 0; i < n; ++i) {
		int x, y; std::cin >> x >> y;
		ordered_x.push_back(Pair{x,y});
		ordered_y.push_back(Pair{x,y});
	}
	std::sort(ordered_x.begin(), ordered_x.end(), cmpx);
	std::sort(ordered_y.begin(), ordered_y.end(), cmpy);
	
	std::multiset<Pair, decltype(cmpx)> set(cmpx);
	
    ll answ = 0;
	
    for (int i = 0; i < n; ++i) {
		if (i != 0 && ordered_y[i].y != ordered_y[i-1].y) {
            for (int j = i-1; j >= 0 && ordered_y[j].y == ordered_y[i-1].y; --j) {
                if (set.find(ordered_y[j]) != set.end()) {
                    set.erase(ordered_y[j]);
                }
            }
        }
		while ((int)set.size() < limit && !ordered_x.empty()) {
			auto p = ordered_x.back(); ordered_x.pop_back();
			if (p.y < ordered_y[i].y) continue;
			set.insert(p);
		}
        if ((int)set.size() == limit) {
			answ = std::max(answ, (ll) set.begin()->x * ordered_y[i].y);
		}
	}
	std::cout << answ;
	return 0;
}