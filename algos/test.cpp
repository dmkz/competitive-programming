#include <bits/stdc++.h>
#include "template.hpp"
#include "debug.hpp"
#include "sparsetable.hpp"
int main() {
    std::vector<int> a = {1,2,3,4};
    SparseTable::SparseTable<int, SparseTable::Min<int>> st(a);
    for (int i = 0; i < isz(a); i++) {
        for (int j = i; j < isz(a); j++) {
            std::cout << "min[" << i << ", " << j << "] = ";
            std::cout << st.calcFunc(i, j) << std::endl;
        }
    }
    std::cout << "a = " << a << std::endl;
}
