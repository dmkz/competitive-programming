#include <stdio.h>
#include <map>

struct Key {
    int16_t a, b, c;
};

inline bool operator<(const Key& l, const Key& r) {
    return l.a < r.a || (l.a == r.a && (l.b < r.b || (l.b == r.b && l.c < r.c)));
}

std::map<Key, int> cache;

int f(int16_t a, int16_t b, int16_t c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return 1;
    }
    
    if (a > 20 || b > 20 || c > 20) {
        return f(20,20,20);
    }
    
    auto key = Key{a,b,c};
    
    auto it = cache.find(key);
    
    if (it != cache.end()) {
        return it->second;
    }
    
    if (a < b && b < c) {
        return cache[key] = f(a,b,c-1)+f(a,b-1,c-1)-f(a,b-1,c);
    }
    
    return cache[key] = f(a-1,b,c)+f(a-1,b-1,c)+f(a-1,b,c-1)-f(a-1,b-1,c-1);
}

int main() {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    printf("%d", f(a,b,c));
    return 0;
}