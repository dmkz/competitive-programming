#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

struct Triple {
    int sum, id, pos; // sum of sequence with identificator = id with erased element on position = pos;
};

bool operator<(const Triple& a, const Triple& b) {
    return a.sum < b.sum || (a.sum == b.sum && (a.id < b.id || (a.id == b.id && a.pos < b.pos)));
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0);
    
    std::vector<Triple> triples;
    int nSeq; std::cin >> nSeq;
    for (int id = 1; id <= nSeq; ++id) {
        int nItems; std::cin >> nItems;
        std::vector<int> items(nItems);
        int sum = 0;
        for (auto& it : items) {
            std::cin >> it;
            sum += it;
        }
        for (int pos = 0; pos < nItems; ++pos) {
            triples.push_back(Triple{sum-items[pos], id, pos+1});
        }
    }
    
    std::sort(triples.begin(), triples.end());
    
    for (int i = 0; i < (int)triples.size(); ++i) {
        auto& cur = triples[i];
        auto it = std::lower_bound(triples.begin()+i, triples.end(), Triple{cur.sum, cur.id+1, 0});
        if (it != triples.end() && it->sum == cur.sum) {
            std::cout << "YES\n";
            std::cout << cur.id << ' ' << cur.pos << '\n';
            std::cout << it->id << ' ' << it->pos << '\n';
            return 0;
        }
    }
    std::cout << "NO";
    return 0;
}