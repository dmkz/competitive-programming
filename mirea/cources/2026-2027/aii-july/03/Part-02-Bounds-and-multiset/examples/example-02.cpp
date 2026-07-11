#include <iostream>
#include <set>
using namespace std;

template <class Iterator>
void print_it(const string &name, Iterator it, Iterator end_it) {
    if (it == end_it) {
        cout << name << " = end" << '\n';
    } else {
        cout << name << " = " << *it << '\n';
    }
}

int main() {
    set<int> s = {2, 5, 8, 10};
    multiset<int> ms = {2, 5, 5, 5, 8, 10};

    print_it("s.lower_bound(6)", s.lower_bound(6), s.end());
    print_it("s.upper_bound(8)", s.upper_bound(8), s.end());

    auto it = s.lower_bound(8);
    if (it != s.begin()) {
        --it;
        cout << "max < 8 = " << *it << '\n';
    }

    print_it("ms.lower_bound(5)", ms.lower_bound(5), ms.end());
    print_it("ms.upper_bound(5)", ms.upper_bound(5), ms.end());
}
