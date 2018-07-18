/*
    Problem: 600E. Lomsat gelral

    Solution: euler tour, mo's algorithm, O(n sqrt(n))
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

struct Query { // struct for query to segment of array from left = l to right = r
    int l, r, id;
};

typedef long long ll;

struct Statistic { // statistic on segment of array, can insert color, remove color, getting answer in O(1)
    
    std::vector<int> count; // count[color] - actual number of current color, where color from 1 to nColors
    
    std::vector<ll> sum;    // sum[count] - actual sum of unique colors for current number of colors
    
    Statistic(const int nColors) {
        count.assign(nColors+1, 0);
        sum.push_back(ll(nColors) * (nColors+1) / 2);
    }
    
    void insert(const int color) {
        auto& cnt = count[color];
        sum[cnt] -= color;
        ++cnt;
        if (cnt >= (int)sum.size()) sum.push_back(0);
        sum[cnt] += color;
    }
    
    void remove(const int color) {
        auto& cnt = count[color];
        sum[cnt] -= color;
        --cnt;
        if ((int)sum.back() == 0) sum.pop_back();
        sum[cnt] += color;
    }
    
    ll answer() const {
        return sum.back();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    // Input colors of vertices, edges of tree:
    int n;
    std::cin >> n;
    
    std::vector<int> color(n);
    for (auto& it : color) {
        std::cin >> it;
    }
    
    std::vector<std::vector<int>> edges(n);
    for (int i = 1; i < n; ++i) {
        int a, b;
        std::cin >> a >> b;
        --a, --b;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    
    // Euler tour on tree:
    
    std::vector<Query> queries;
    
    std::vector<int> arr;
    
    std::function<void(int,int)> visit = [&](const int curr, const int parent){
        int left = (int)arr.size();
        arr.push_back(color[curr]);
        for (auto next : edges[curr]) {
            if (next != parent) {
                visit(next, curr);
            }
        }
        int right = (int)arr.size()-1;
        queries.push_back(Query{left, right, curr});
    };
    
    visit(0, -1);
    
    // Mo's algorithm for queries offline:
    
    const int GSIZE = 256;
    
    std::sort(queries.begin(), queries.end(), [](const Query& a, const Query& b) {
        if (a.l / GSIZE != b.l / GSIZE) {
            return a.l < b.l;
        }
        return a.r < b.r;
    });
    
    Statistic stat(n);
    
    std::vector<ll> answer(n);
    
    int left = 0, right = -1;
    
    for (const auto& q : queries) {
        while (right < q.r) {
            stat.insert(arr[right+1]);
            ++right;
        }
        while (left < q.l) {
            stat.remove(arr[left]);
            ++left;
        }
        while (left > q.l) {
            stat.insert(arr[left-1]);
            --left;
        }
        while (right > q.r) {
            stat.remove(arr[right]);
            --right;
        }
        answer[q.id] = stat.answer();
    }
    
    // Output:
    for (auto& it : answer) {
        std::cout << it << ' ';
    }
    
    return 0;
}