#include <algorithm>
#include <iostream>
#include <string>

int main() {
  std::string a, b, c;
  std::cin >> a >> b >> c;
  std::cout << std::max({a, b, c}, [](auto l, auto r) {
    return l.size() != r.size() ? l.size() < r.size() : l < r;
  }) << std::endl;
  return 0;
}
