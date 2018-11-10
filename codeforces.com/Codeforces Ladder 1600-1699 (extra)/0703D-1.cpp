/*
    Problem: 703D. Mishka and Interesting sum
    
    Solution: Fenwick tree, coordinate compression, sorting, O((n+m)*(log(n)+log(m)))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <algorithm>

char getChar() {
    static char buffer[1 << 20];
    static int size = 0;
    static int pos = 0;
    if (pos == size) {
        size = (int)fread(buffer, 1, 1 << 20, stdin), pos = 0;
    }
    if (pos == size) {
        return -1;
    }
    return buffer[pos++];
}

void putChar(char c) {
    static char buffer[1 << 20];
    static int size = 0;
    if (size == (1 << 20) || c == -1) {
        fwrite(buffer, 1, size, stdout), size = 0;
    }
    if (c != -1) buffer[size++] = c;
}

int read() {
    char c = '?';
    while (!(c == '-' || ('0' <= c && c <= '9'))) { c = getChar(); };
    bool neg = false; int res = 0;
    if (c == '-') { neg = true, c = getChar(); }
    while ('0' <= c && c <= '9') { (res *= 10) += (c - '0'), c = getChar(); }
    return neg ? -res : res;
}

void writeln(int v) {
    static char stack[15];
    int size = 0, neg = 0;
    if (v < 0) { neg = true, v = -v; }
    do { stack[size++] = char('0' + v % 10), v /= 10; } while (v > 0);
    if (neg) { stack[size++] = '-'; }
    while (size--) { putChar(stack[size]); }
    putChar('\n');
}

struct Fenwick {
    
    std::vector<int> data;
    
    Fenwick(int n) : data(n+1, 0) { }
    
    void inc(int p, int delta) {
        for (int i = p+1; i < (int)data.size(); i |= i+1) {
            data[i] ^= delta;
        }
    }
    
    int get(int r) const {
        int ret = 0;
        for (int i = r+1; i >= 0; (i &= i+1)--) {
            ret ^= data[i];
        }
        return ret;
    }
    
    int get(int l, int r) const {
        return get(r) ^ get(l-1);
    }
};

struct Query {
    int l, r, id;
};

int main() {
    int n = read();
    std::vector<int> arr(n), item, pref{0};
    for (auto& it : arr) {
        item.push_back(it = read());
        pref.push_back(pref.back() ^ it);
    }
    std::sort(item.begin(), item.end());
    item.erase(std::unique(item.begin(), item.end()), item.end());
    for (auto& it : arr) {
        it = int(std::lower_bound(item.begin(), item.end(), it) - item.begin());
    }
    {
        std::vector<int> order(n, -1); int counter = 0;
        for (auto& it : arr) {
            if (order[it] == -1) {
                order[it] = counter++;
            }
            it = order[it];
        }
        std::vector<int> temp(item.size());
        for (int i = 0; i < (int)item.size(); ++i) {
            temp[order[i]] = item[i];
        }
        item.assign(temp.begin(), temp.end());
    }
    int m = read();
    std::vector<Query> queries(m);
    for (int i = 0; i < m; ++i) {
        auto &q = queries[i];
        q.l = read()-1, q.r = read()-1;
        q.id = i;
    }
    std::sort(queries.begin(), queries.end(), [](const Query& a, const Query& b) {
        return a.r < b.r || (a.r == b.r && a.l < b.l);
    });
    std::vector<int> lastPos(item.size(), -1), answ(m);
    Fenwick fw(n);
    int r = -1;
    for (auto& q : queries) {
        while (r < q.r) {
            ++r;
            int index = arr[r];
            if (lastPos[index] != -1) {
                fw.inc(lastPos[index], item[index]);
            }
            fw.inc(lastPos[index] = r, item[index]);
        }
        answ[q.id] = pref[q.r+1] ^ pref[q.l] ^ fw.get(q.l, q.r);
    }
    for (auto it : answ) {
        writeln(it);
    }
    putChar(-1);
    return 0;
}