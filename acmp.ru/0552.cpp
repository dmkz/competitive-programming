#pragma GCC diagnostic ignored "-Wunused-result"
#include <stdio.h>
#include <bits/stdc++.h>

typedef long long ll;

int main() {
    int n; 
    scanf("%d", &n);
    
    std::vector<int> a(n, 0); 
    for (auto& it : a) scanf("%d", &it);
    
    // s1[i] = a[i] + a[i+1] + a[i+2] + ... + a[n-1]
    std::vector<ll> s1(n+1, 0); 
    for (int i = n-1; i >= 0; --i) s1[i] = s1[i+1] + a[i];
    
    // s2[i] = a[i] * (a[i+1] + a[i+2] + ... + a[n-1]) + a[i+1] * (a[i+2] + ... ) + ...
    std::vector<ll> s2(n+1, 0); 
    for (int i = n-1; i >= 0; --i) {
        s2[i] = a[i] * s1[i+1] + s2[i+1];
    }
    
    // Sum all a[i] * a[j] * a[k] for 0 <= i < j < k < n
    ll answer = 0;
    for (int i = 0; i < n-2; ++i) {
        answer += a[i] * s2[i+1];
    }
    std::cout << answer << std::endl;
    return 0;
}