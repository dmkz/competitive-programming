/*
    Problem: 703D. Mishka and Interesting sum
    
    Solution: Mo's algorithm, prefix sums, xor, two pointers, O(n * log(n) + q * sqrt(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <random>
#include <chrono>
#include <memory>

#define all(x) (x).begin(), (x).end()
#define size(x) (int)(x).size()
#define unique(x) (x).erase(std::unique(all((x))), (x).end())
#define lowpos(x, y) int(std::lower_bound(all((x)), (y)) - (x).begin())

typedef std::vector<int> vi;

char getChar() {
    static char buf[1 << 20];
    static int pos = 0;
    static int size = 0;
    if (pos == size) {
        size = (int)fread(buf, 1, 1 << 20, stdin);
        pos = 0;
    }
    if (pos == size) {
        return EOF;
    }
    return buf[pos++];
}
 
 
template<typename T>
inline void read(T& v) {
    char c = '?';
    while (!(c == '-' || ('0' <= c && c <= '9'))) c = getChar();
    bool positive = true;
    if (c == '-') {
        positive = false;
        c = getChar();
    }
    v = 0;
    while ('0' <= c && c <= '9') {
        (v *= 10) += (c - '0');
        c = getChar();
    }
    if (!positive) v = -v;
}
 
void putChar(char c) {
    static char buf[1 << 20];
    static int size = 0;
    if (size == 1 << 20 || c == -1) {
        fwrite(buf, 1, size, stdout);
        size = 0;
    }
    if (c != -1) {
        buf[size++] = c;
    }
}
 
inline void writeln(int v) {
    static int stack[15];
    int size = 0;
    do {
        stack[size++] = v % 10;
        v /= 10;
    } while (v > 0);
    while (size--) {
        putChar(char(stack[size]+'0'));
    }
    putChar('\n');
}

struct Query {
    int l, r, id;
};

struct Item {
    int value, count;
    
    Item(int value_ = 0, int count_ = 0) : value(value_), count(count_) { }
};

bool operator<(const Item& a, const Item& b) {
    return a.value < b.value || (a.value == b.value && a.count < b.count);
}

bool operator==(const Item& a, const Item& b) {
    return a.value == b.value && a.count == b.count;
}

vi solve(const int n, const int m, vi arr, const vi& lt, const vi& rt) {
    // Coordinate compression and calculating xor-sums on prefixes:
    vi pref_xor{0};
    std::vector<Item> item;
    item.reserve(n);
    pref_xor.reserve(1+n);
    for (auto it : arr) {
        item.push_back(Item{it, 0});
        pref_xor.push_back(pref_xor.back() ^ it);
    }
    std::sort(all(item));
    unique(item);
    for (int i = 0; i < n; ++i) {
        arr[i] = lowpos(item, Item(arr[i], 0));
    }
    // Rearrange items in order from left to right in array:
    {
        vi order(size(item), -1);
        int counter = 0;
        for (int& it : arr) {
            if (order[it] == -1) {
                order[it] = counter++;
            }
            it = order[it];
        }
        std::vector<Item> temp(size(item));
        for (int i = 0; i < size(item); ++i) {
            temp[order[i]] = item[i];
        }
        item.assign(temp.begin(), temp.end());
    }
    // Sorting queries using Mo's compare function:
    std::vector<Query> queries(m);
    for (int i = 0; i < m; ++i) {
        queries[i] = Query{lt[i]-1,rt[i]-1,i};
    }
    uint64_t seed = (uint64_t)std::chrono::high_resolution_clock::now().time_since_epoch().count();
    seed ^= (uint64_t)(std::make_unique<char>().get());
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> dist(970, 1030);
    const int gsize = dist(gen);
    std::sort(all(queries), [&](const Query& a, const Query& b) {
        const int ga = a.l / gsize;
        const int gb = b.l / gsize;
        if (ga == gb) {
            return (ga & 1) ? a.r < b.r : a.r > b.r;
        } else {
            return a.l < b.l;
        }
    });
    // Calculating answer for queries:
    vi answer(m);
    int l = 0, r = -1, xorUniq = 0;
    for (auto q : queries) {
        while (r < q.r) {
            Item& it = item[arr[++r]];
            xorUniq ^= (it.count++ == 0) ? it.value : 0;
        }
        while (l < q.l) {
            Item& it = item[arr[l++]];
            xorUniq ^= (it.count-- == 1) ? it.value : 0;
        }
        while (l > q.l) { 
            Item& it = item[arr[--l]];
            xorUniq ^= (it.count++ == 0) ? it.value : 0;
        }
        while (r > q.r) {
            Item& it = item[arr[r--]];
            xorUniq ^= (it.count-- == 1) ? it.value : 0;
        }
        answer[q.id] = pref_xor[r + 1] ^ pref_xor[l] ^ xorUniq;
    }
    return answer;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n, m;
    read(n);
    vi arr(n);
    for (int i = 0; i < n; ++i) { read(arr[i]); }
    read(m);
    vi lt(m), rt(m);
    for (int i = 0; i < m; ++i) { read(lt[i]), read(rt[i]); }
    vi answ = solve(n, m, arr, lt, rt);
    for (auto it : answ) {
        writeln(it);
    }
    putChar(-1);
    return 0;
}