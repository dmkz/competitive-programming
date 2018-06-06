#include <iostream>

int main() {
    int x; std::cin >> x;
    auto a = std::to_string(x-1);
    auto b = std::to_string(x+1);
    std::cout << (a.size() > b.size() ? b : a);    
    return 0;
}