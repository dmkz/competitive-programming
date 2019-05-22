/*
    Задача: 974. Странный ним
    
    Решение: теория игр, ним, исследование, O(t)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/
#include <iostream>
int main() {
    for (int a, b, c; std::cin >> a >> b >> c, a; ) {
        printf("%s wins the game.\n", (a+1)^(b+1)^(c+1) ? "Alice" : "Bob");
    }
    return 0;
}