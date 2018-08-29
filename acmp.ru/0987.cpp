/*
    Задача: 987. Обмен пакетами
    
    Решение: строки, реализация, O(n)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>
#include <cassert>
#include <cmath>

int main() {
    std::string command, name;
    std::cin >> command >> name;
    assert(command == "ping");
    int sum = 0, min = 10001, max = 0, lost = 0;
    for (int i = 0; i < 4; ++i) {
        std::cin >> command;
        assert(command == "Time" || command == "Reply");
        if (command == "Time") {
            lost++;
            std::cin >> command;
            assert(command == "out");
        } else {
            std::cin >> command;
            assert(command == "from");
            std::cin >> command;
            assert(command == name);
            int value = 0;
            int code = scanf(" Time=%d", &value);
            assert(code == 1);
            min = std::min(min, value);
            max = std::max(max, value);
            sum += value;
        }
    }
    std::cout << "Ping statistics for " << name << ":\n";
    std::cout << "Packets: Sent = 4 Received = " << 4 - lost << " Lost = " << lost << " (" << 25*lost << "% loss)\n";
    if (lost == 4) return 0;
    std::cout << "Approximate round trip times:\n";
    std::cout << "Minimum = " << min << " Maximum = " << max << " Average = " << (int)std::round(1.0 * sum / (4 - lost));
    return 0;
}