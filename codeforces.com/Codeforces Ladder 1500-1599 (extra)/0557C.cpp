/*
    Problem: 557C. Arthur and Table
    
    Solution: dynamic programming, Sqrt-List, O(n sqrt(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

struct Pair {
    int value, cost;
};

struct SqrtList {

    const int GSIZE = 128;

    std::vector<std::vector<int>> data;
    
    std::vector<int> sum;
    
    SqrtList() {
        data.assign(1, std::vector<int>());
        sum.assign(1, 0);
    }
    
    int get_sum(int k) const {
        if (k <= 0) return 0;
        int ret = 0;
        for (int g = 0; g < (int)data.size(); ++g) {
            if ((int)data[g].size() < k) {
                k -= (int)data[g].size();
                ret += sum[g];
            } else {
                for (int i = 0; i < k; ++i) {
                    ret += data[g][i];
                }
                return ret;
            }
        }
        assert(false);
    }
    
    void insert(int value) {
        if (data[0].empty()) {
            data[0].push_back(value);
            sum[0] += value;
            return;
        }
        for (int g = 0; g < (int)data.size(); ++g) {
            if (data[g].back() >= value || g == (int)data.size()-1) {
                data[g].push_back(value);
                for (int i = (int)data[g].size()-2; i >= 0; --i) {
                    if (data[g][i] > data[g][i+1]) {
                        std::swap(data[g][i], data[g][i+1]);
                    } else {
                        break;
                    }
                }
                sum[g] += value;
                if ((int)data[g].size() == 2 * GSIZE) {
                    data.insert(data.begin()+g+1, std::vector<int>(data[g].begin()+GSIZE, data[g].end()));
                    int tsum = 0;
                    for (auto& it : data[g+1]) tsum += it;
                    sum.insert(sum.begin()+g+1, tsum);
                    data[g].resize(GSIZE);
                    sum[g] = 0;
                    for (auto& it : data[g]) sum[g] += it;
                }
                return;
            }
        }
        assert(false);
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n; std::cin >> n;
    std::vector<Pair> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i].value;
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i].cost;
    }
    
    std::sort(arr.begin(), arr.end(), [](const Pair& a, const Pair& b) {
        return a.value < b.value || (a.value == b.value && a.cost < b.cost);
    });
    
    SqrtList list;
    std::vector<int> suff{0};
    for (int i = 0; i < n; ++i) {
        suff.push_back(suff.back()+arr[i].cost);
    }
    int min = (int)1e9+1;
    for (int i = 0; i < n; ++i) {
        if (i > 0 && arr[i].value == arr[i-1].value) {
            list.insert(arr[i].cost);
            continue;
        }
        int j = i;
        while (j < n && arr[j].value == arr[i].value) ++j;
        int k = i-(j-i-1);
        min = std::min(min, suff[n]-suff[j] + list.get_sum(k));
        list.insert(arr[i].cost);
    }
    std::cout << min;
    return 0;
}   