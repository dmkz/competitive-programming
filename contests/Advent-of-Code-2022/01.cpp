#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
const bool easy_version = false;
int main() {
    std::vector<int64_t> v;
    std::string s;
    while(std::getline(std::cin, s)) {
        if (v.empty() || isz(s) == 0) {
            v.push_back(0);
        }
        if (isz(s)) {
            v.back() += std::stoll(s);
        }
    }
    if(easy_version) {
        std::cout << *std::max_element(all(v)) << std::endl;
    } else {
        std::sort(all(v),std::greater<>());
        std::cout << std::accumulate(v.begin(),v.begin()+3,0LL) << std::endl;
    }
    
}