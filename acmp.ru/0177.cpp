/*
    Задача: 177. Склад
    
    Решение: моделирование, O(n*m)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
typedef std::pair<int,int> pii;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
struct Robot {
    vi cap;
    std::vector<std::vector<pii>> data;
    Robot(int nCells) {
        data.resize(1+nCells);
        cap.resize(1+nCells);
    }
    void set_cap(int id, int c) {
        cap[id] = c;
    }
    
    int choose_cell(pii cargo) {
        pii best(INT_MAX,0);
        for (int i = 1; i < isz(cap); ++i) {
            if (cap[i] - cargo.second >= 0) {
                best = std::min(best, pii(cap[i] - cargo.second, i));
            }
        }
        return best.second;
    }
    
    bool try_move(pii cargo) {
        auto best = std::make_tuple(
            INT_MAX, 
            INT_MAX,
            INT_MAX,
            INT_MAX,
            INT_MAX,
            INT_MAX);
        for (int i = 1; i < isz(cap); ++i) {
            for (auto & curr : data[i]) {
                if (cap[i] + curr.second >= cargo.second) {
                    for (int j = 1; j < isz(cap); ++j) {
                        if (j == i) { continue; }
                        if (cap[j] >= curr.second) {
                            auto temp = std::make_tuple(
                                curr.second, 
                                cap[i] + curr.second,
                                cap[j] - curr.second,
                                curr.first,
                                j,i);
                            best = std::min(best, temp);
                        }
                    }
                }
            }
        }
        if (std::get<0>(best) == INT_MAX) {
            return false;
        }
        auto moved = pii(std::get<3>(best),  std::get<0>(best));
        const int i = std::get<5>(best);
        const int j = std::get<4>(best);
        move_cargo(moved, i, j);
        put_cargo(cargo, i);
        return true;
    }
    
    void put_cargo(pii cargo, int c) {
        data[c].push_back(cargo);
        cap[c] -= cargo.second;
        assert(cap[c] >= 0);
        std::cout << "put cargo " << cargo.first << " to cell " << c << std::endl;
    }
    
    void move_cargo(pii cargo, int from, int to) {
        auto it = std::find(all(data[from]), cargo);
        assert(it != data[from].end());
        cap[from] += cargo.second;
        data[from].erase(it);
        data[to].push_back(cargo);
        cap[to] -= cargo.second;
        assert(cap[to] >= 0 && cap[from] >= 0);
        std::cout << "move cargo " << cargo.first << " from cell " << from << " to cell " << to << std::endl;
    }
    
    void pop(pii cargo) {
        bool was = false;
        for (int i = 1; i < isz(cap); ++i) {
            auto it = std::find(all(data[i]), cargo);
            if (it == data[i].end()) {
                continue;
            }
            was = true;
            data[i].erase(it);
            cap[i] += cargo.second;
            std::cout << "take cargo " << cargo.first << " from cell " << i << std::endl;
            break;
        }
        //assert(was);
    }
    
    void put(pii cargo) {
        int target = choose_cell(cargo);
        if (target == 0) {
            bool flag = try_move(cargo);
            if (!flag) {
                std::cout << "cargo " << cargo.first << " cannot be stored" << std::endl;
            }
            return;
        }
        put_cargo(cargo,target);
    }
};
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    for (int nCells, nCargos; std::cin >> nCells >> nCargos; ) {
        Robot robot(nCells);
        for (int i = 1; i <= nCells; ++i) {
            int cap; std::cin >> cap;
            robot.set_cap(i, cap);
        }
        vi size(nCargos+1), tin(nCargos+1), tout(nCargos+1);
        std::set<pii> events;
        for (int i = 1; i <= nCargos; ++i) {
            std::cin >> size[i] >> tin[i] >> tout[i];
            events.insert(pii( tin[i], +i));
            events.insert(pii(tout[i], -i));
        }
        while (!events.empty()) {
            auto curr = *events.begin(); events.erase(events.begin());
            if (curr.second > 0) {
                const int id = curr.second;
                robot.put(pii(id, size[id]));
            } else {
                const int id = -curr.second;
                robot.pop(pii(id, size[id]));
            }
        }
    }
    return 0;
}