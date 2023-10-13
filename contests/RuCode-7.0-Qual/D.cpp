#include "template.hpp"
int main() {
    int q; std::cin >> q;
    std::deque<int> deque;
    std::multiset<int> set;
    while (q --> 0) {
        std::string s;
        std::cin >> s;
        if (s == "enqueue") {
            int n; std::cin >> n;
            deque.push_back(n);
            set.insert(n);
            std::cout << "ok\n";
        } else if (s == "dequeue") {
            if (!deque.empty()) {
                auto x = deque.front();
                set.erase(set.find(x));
                deque.pop_front();
                std::cout << x << "\n";
            } else std::cout << "error\n";
        } else if (s == "front") {
            if (!deque.empty()) 
                std::cout << deque.front() << "\n";
            else std::cout << "error\n";
        } else if (s == "size") {
            std::cout << deque.size() << "\n";
        } else if (s == "clear") {
            deque.clear();
            set.clear();
            std::cout << "ok\n";
        } else if (s == "min") {
            if (!deque.empty()) 
                std::cout << *set.begin() << "\n";
            else std::cout << "error\n";
        }
    }
}
