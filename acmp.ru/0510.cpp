#include <iostream>
#include <vector>

/*
    Варианты:
    1. Все вертикально
    ..11
    ..22
    ..33
    
    2. Одну вертикально - две другие горизонтально х2
    ..11
    ..23
    ..23
    
    ..23
    ..23
    ..11
    3. Когда заполняется не полностью:
    6441
    6331
    5522
    
    
*/

int main() {
    int n; std::cin >> n;
    std::vector<int> count(1+n);
    count[0] = 1;
    if (n >= 2) {
        count[2] = 3;
    }
    for (int curr = 3; curr <= n; ++curr) {
        count[curr] = 3 * count[curr-2];
        for (int prev = curr-4; prev >= 0; prev -= 2) {
            count[curr] += 2 * count[prev];
        }
    }
    std::cout << count[n] << std::endl;
    return 0;
}