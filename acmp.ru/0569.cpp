#include <stdio.h>
#include <vector>
#include <algorithm>
#include <tuple>
#include <cassert>

struct Pair {
    int cost, id;
};

int main() {
    int n, d;
    scanf("%d %d", &n, &d);
    
    std::vector<Pair> arr;
    for (int i = 1; i <= n; ++i) {
        int cost; scanf("%d", &cost);
        arr.push_back(Pair{cost,i});
    }
    
    std::stable_sort(arr.begin(), arr.end(), [](const Pair& a, const Pair& b) {
        return a.cost < b.cost;
    });
    
    std::vector<int> curr(n, d);
    
    std::vector<Pair> answer(1+n, Pair{0,0});
    
    int low = 0, high = n-1;
    while (low < high) {
        int diff = curr[low] - arr[low].cost;
        if (diff == 0) {
            for (int i = 0; i < n; ++i) {
                assert(curr[i] == arr[i].cost);
            }
            break;
        }
        answer[arr[low].id] = Pair{diff, arr[high].id};
        curr[low] -= diff;
        curr[high] += diff;
        while (curr[high] > arr[high].cost) {
            int diff = curr[high] - arr[high].cost;
            curr[high] -= diff;
            curr[high-1] += diff;
            answer[arr[high].id] = Pair{diff, arr[high-1].id};
            --high;
        }
        ++low;
    }
    
    for (int i = 1; i <= n; ++i) {
        const auto& t = answer[i];
        printf("%d %d\n", t.id, t.cost);
    }
    
    return 0;
}