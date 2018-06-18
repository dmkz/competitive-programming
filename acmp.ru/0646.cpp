/*
    Решение динамикой по суммам, но вместо ответа на задачу будем считать ответ на обратную задачу.
    
    Сколько есть способов распределить суммы, чтобы одному из них досталось < k.
    
    Это можно сделать за O(n*k). В силу симметрии, ответ нужно умножить на 2.
*/

#include <stdio.h>
#include <vector>
#include <iostream>

typedef long long ll;

ll solve(int k, const std::vector<int>& a) {
    const int n = a.size();
    ll sum = 0;
    for (auto& it : a) {
        sum += it;
    }
    if (sum < 2 * k || n == 1) {
        return 0;
    }
    std::vector<ll> curr(k), next(k);
    curr[0] = 1;
    for (auto elem : a) {
        for (int s = 0; s < k; ++s) {
            next[s] = curr[s] + (s >= elem ? curr[s-elem] : 0);
        }
        next.swap(curr);
    }
    sum = 0;
    for (auto& it : curr) {
        sum += it;
    }
    return (ll(1) << n) - 2 * sum;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
       
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    
    std::cout << solve(k, a);   
    
    return 0;
}